#!/usr/bin/perl

use Tk;
use Tk::TableMatrix::Spreadsheet;
use Spreadsheet::ParseExcel;
use Spreadsheet::ParseExcel::SaveParser;
use Spreadsheet::ParseExcel::SaveParser::Workbook;
use Spreadsheet::ParseExcel::SaveParser::Worksheet;
use Spreadsheet::WriteExcel;
##use strict;


## Глобальные переменные

$filename = "" ; ## $filename  "db_mailing_customers.xls"
$arrayVar = () ; ## массив значений из таблицы
$arrayFor = () ; ## массив значений Формата ячеек
$arrayVar2 = () ; ## массив значений из таблицы
$strsearch = "" ; ## строка поиска
 @mC = ();  ## ширина полей таблицы
 $icols = 0;
 $irows = 0;

 $arrS = (); ## поиск
 @mk = () ;
 @uniq = () ;
 $find_update = 0 ;


#Основа

$oExcel = new Spreadsheet::ParseExcel::SaveParser ;
$oBook = "" ;

$mw = MainWindow->new;
$mw->configure(-title=>"db_mailing_customers");
$mw->minsize(qw(700 400));
$menu = $mw->Frame()->pack(-side=>"top",-fill=>"x");
$menu_file = $menu->Menubutton(-text=>"File",-tearoff=>"false")->pack(-side=>"left");
$menu_file->command(-label=>"Open",-command=>\&bOpen );
$menu_file->command(-label=>"Save",-command=>\&bSave );
##$menu_file->command(-label=>"SaveAs",-command=>\&bSaveAs );
$menu_file->command(-label=>"Exit",-command=>[$mw => 'destroy'] );
$Lab1=$mw->Label(-text => 'Search ')->pack;
$Edit=$mw->Entry(-width => 60,-textvariable=>\$strsearch )->pack;
$But1=$mw->Button(-text=>"Find",-height=>1,-width=>15,-command =>\&sFind )->pack;
$But2=$mw->Button(-text=>"Clear\\Update",-height=>1,-width=>15,-command =>\&bClear )->pack;

$frame = $mw->Frame(-relief=>"groove",-borderwidth=>"3")->pack(-fill=>"both",-pady=>"0");

# строим начальную таблицу (более для красоты)
CreateTb();

Tk::MainLoop();


sub bClear
{
  $strsearch = "" ;

  if ($find_update==1) {

   my ($idx) ;
   my ($r,$c,$k,$v,$f) ;

   foreach $k (sort keys $arrS) {
    ($idx,$c) = split(/,/,$k,2) ;
    next if ($idx==0);
    $r = $uniq[$idx];
    if ($arrayVar->{"$r,$c"} ne $arrS->{"$idx,$c"}) {
      $arrayVar->{"$r,$c"} = $arrS->{"$idx,$c"};
    }
   }

   $find_update=0;
  }

   # удаляем отображаемую таблицу
  $table->pack('forget');
  ##$table->selectionClearall(0,"end");
  ##$table->clear(all);
  ##$table->delete('end');

  # строим новую таблицу
  @border = (0,0,0,1);

  $table = $frame->Scrolled("Spreadsheet",
-cols => $icols,
-rows => $irows + 10,   ## расширяем хеш (массив строк) еще на 50 строк.
-width => 5, -height => 10,
-titlerows => 1,
-variable => $arrayVar,
-selectmode => "extended",
-selecttype => "row",
-resizeborders => "col",
-bg => "white",
-rowheight => 2,
-bd => \@border,
-justify => "left",
-drawmode => "compatible",
-wrap => 0,
-relief => "solid"
)->pack(-fill=>"both");
  $table->rowHeight(0,1);
  $table->tagRow("title",0);
  $table->tagConfigure("title", -bd=>2, -relief=>"raised");
  $table->colWidth(@mC);

  return ;
}


sub bOpen
{
  ##my $filename1 = shift @$_ ;
  ##if ($filename1 eq "") {

    my @types = (["Excel files", '.xls'],
       ["All Files", "*"] );
    my $filename1 = $mw->getOpenFile(-filetypes => \@types,
      -initialfile=> 'db_mailing_customers.xls',
      -defaultextension => '.xls');

  ##}

  if ($filename1 eq "") { return ; }
  $filename = $filename1 ;

  my @mleniC = () ;
  my $mlenC = 0 ;

  $oBook = $oExcel->Parse($filename);

  if ( !defined $oBook ) {
    die $parser->error(), ".\n";
  }

  my($iR, $iC, $oWkS, $oWkC);

  ## выделяем те колонки которые будем редактировать
  @ls = ( 'company' , 'position' , 'lastname' , 'firstname' ,
           'middlename' , 'fax_number' , 'email' , 'additational_emails' ) ;
  @lsi = ( );


  for(my $iSheet=0; $iSheet < $oBook->{SheetCount} ; $iSheet++) {
   $oWkS = $oBook->{Worksheet}[$iSheet];

   if (defined $oWkS->{MaxCol}) { $icols=$oWkS->{MaxCol} + 1; }
   if (defined $oWkS->{MaxRow}) { $irows=$oWkS->{MaxRow} + 1; }


   my $iRc = 0 ;
   my $iCc = 0 ;

   for( $iC = $oWkS->{MinCol} ; defined $oWkS->{MaxCol} && $iC <= $oWkS->{MaxCol} ; $iC++) {
     $iR = $oWkS->{MinRow} ;
     $oWkC = $oWkS->{Cells}[$iR][$iC];
     if($oWkC) {
       foreach $vl (@ls) {
        if (defined($oWkC->Value) && ($oWkC->Value eq $vl)) {

         for( $iR = $oWkS->{MinRow} ; defined $oWkS->{MaxRow} && $iR <= $oWkS->{MaxRow} ; $iR++) {
          $oWkC = $oWkS->{Cells}[$iR][$iC];
          if($oWkC) {
            $arrayFor->{"$iR,$iCc"} = $oWkC->{FormatNo}; # Get the format from the cell
            $arrayVar->{"$iR,$iCc"} = $oWkC->Value ;
            #находим ширину max(Колонки)
            if (!defined($mleniC[$iCc])) { $mleniC[$iCc] = 0 ; }
            $mlenC = length($oWkC->Value) ;
            if ($mlenC>$mleniC[$iCc]) { $mleniC[$iCc]= $mlenC ;}
          }
         }

         $lsi[$iCc] = $iC ; ## храним индексы в реальной табл
         $iCc = $iCc + 1 ;


        }
       }
     }
   }

   $icols = $iCc  ;

  }

  ##$oWkS->close();

  ## рассчитываем ширину полей колонок + 4
  @mC = ();
  my ($j0, $jc ) = ( 0, 0) ;
  foreach $i ( @mleniC ) {
   $mC[$j0]=$jc;  $j0++;
   $mC[$j0]=$i+4; $j0++;
   $jc++;
  }

  bClear ;

  return ;
}


sub bSave
{
 #if ($filename eq "") { bSaveAs()  ; }

 $oBook = $oExcel->Parse($filename);

 if ( !defined $oBook ) {
   die $parser->error(), ".\n";
 }

 my $workbook;

 {
  # SaveAs generates a lot of harmless warnings about unset
  # Worksheet properties. You can ignore them if you wish.
  local $^W = 0;

  # Write data to some cells
  my($oWkS);
  for(my $iSheet=0; $iSheet < $oBook->{SheetCount} ; $iSheet++) {
   $oWkS = $oBook->{Worksheet}[$iSheet];
   my ($r,$c,$k,$v,$f) ;
   foreach $k (keys $arrayVar) {
     $v = $arrayVar->{$k} ;
     ($r,$c) = split(/,/,$k,2) ;
     $f = "";
     if (defined $arrayFor->{$k}) { $f = $arrayFor->{$k} ; }

         $c = $lsi[$c] ;

     $oBook->AddCell($iSheet, $r, $c, $v, $f );
   }
  }

  # Rewrite the file or save as a new file
  $workbook = $oBook->SaveAs($filename); ## 'new.xls'
 }

 $workbook->close();

 $mw->messageBox(-message=>"File: $filename - saving",-type=>'ok');

}

sub bSaveAs
{
 my @types = (["Excel files", '.xls'],
       ["All Files", "*"] );

 my $filename1 = $mw->getSaveFile(-filetypes => \@types,
      -initialfile=> 'db_mailing_customers',
      -defaultextension => '.xls');

 if ($filename1 ne "") {
     $filename = $filename1;
     bSave() ; # Save the file ...
 }

}


sub CreateTb
{
@border = (0,0,0,1);

$arrayVar->{"0,0"} = "A";
$arrayVar->{"0,1"} = "B";
$arrayVar->{"0,2"} = "C";
$arrayVar->{"0,3"} = "D";
$arrayVar->{"0,4"} = "E";
$arrayVar->{"0,5"} = "F";

$table = $frame->Scrolled("Spreadsheet",
-cols => 6,
-width => 5, -height => 10,
-titlerows => 1,
-variable => $arrayVar,
-selectmode => "multiple",
-selecttype => "row",
-resizeborders => "col",
-bg => "white",
-rowheight => 2,
-bd => \@border,
-justify => "left",
-drawmode => "compatible",
-wrap => 0,
-relief => "solid"
)->pack(-fill=>"both");
$table->rowHeight(0,1);
$table->tagRow("title",0);
$table->tagConfigure("title", -bd=>2, -relief=>"raised");
}


sub sFind
{
 return if ($strsearch eq "");

 $arrS = ();
 @mk = () ;

 my $idx = 0 ;
 $mk[$idx]=0 ;
 my ($r,$c,$k,$v,$f) ;
 foreach $k (keys $arrayVar) {
  $v = $arrayVar->{$k} ;
  ($r,$c) = split(/,/,$k,2) ;
  if ($v=~/$strsearch/i) { $idx++ ; $mk[$idx]=$r ; }
 }

 ##print "@mk\n";
 ## убираем повторяющиеся элементы
 my %hash=();
 @uniq=grep{!$hash{$_}++} @mk;
 ##@uniq=@mk;
 ##print "@uniq\n";

 $idx = 0 ;
 foreach $k (sort keys $arrayVar) {
  ($r,$c) = split(/,/,$k,2) ;
  for ($idx=0;$idx< @uniq ; $idx++ ) {
    if ($uniq[$idx]==$r)  {
       $arrS->{"$idx,$c"} = $arrayVar->{$k} ;
       last ;
    }
  }
 }

   # удаляем отображаемую таблицу
  $table->pack('forget');
  ##$table->selectionClearall(0,"end");
  ##$table->clear(all);
  ##$table->delete('end');

  # строим новую таблицу
  @border = (0,0,0,1);

  $table = $frame->Scrolled("Spreadsheet",
-cols => $icols,
-rows => $#uniq + 1 ,
-width => 5, -height => 10,
-titlerows => 1,
-variable => $arrS,
-selectmode => "extended",
-selecttype => "row",
-resizeborders => "col",
-bg => "white",
-rowheight => 2,
-bd => \@border,
-justify => "left",
-drawmode => "compatible",
-wrap => 0,
-relief => "solid"
)->pack(-fill=>"both");
  $table->rowHeight(0,1);
  $table->tagRow("title",0);
  $table->tagConfigure("title", -bd=>2, -relief=>"raised");
  $table->colWidth(@mC);

  $find_update = 1 ;

  return ;


}


 ## &bOpen "db_mailing_customers.xls" ;



__END__