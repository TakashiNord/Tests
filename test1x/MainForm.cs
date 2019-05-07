/*
 * Created by SharpDevelop.
 * User:
 * Date: 21.06.2016
 * Time: 9:11
 *
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;
using System.Linq;

namespace test1x
{
  /// <summary>
  /// Description of MainForm.
  /// </summary>
  public partial class MainForm : Form
  {
    public MainForm()
    {
      //
      // The InitializeComponent() call is required for Windows Forms designer support.
      //
      InitializeComponent();

      //
      // TODO: Add constructor code after the InitializeComponent() call.
      //
    }

    void AddLogString(string s)
    {
      DateTime d = DateTime.Now;
      string strout = "\n"+ "[" + d.ToLongTimeString() + "] " + s ;
      if(InvokeRequired) {
          richTextBox1.Invoke((Action)delegate { richTextBox1.AppendText(strout); });
          richTextBox1.Invoke((Action)delegate { richTextBox1.Update(); });
      } else {
          richTextBox1.AppendText(strout);
          richTextBox1.Update();
        }
      Application.DoEvents();
    }

    void AddFile(object FilePath)
    {
      string[] arr = new string[4];
      ListViewItem itm ;

      string file=(string)FilePath ;

      System.IO.FileInfo fileinfo = new System.IO.FileInfo(file);
      long size = fileinfo.Length;
      int sz = Convert.ToInt32(size); //  /(1024*1024)

      arr[0] = System.IO.Path.GetFileName(file);
      arr[1] = sz.ToString();
      arr[2] = "";
      arr[3] = System.IO.Path.GetDirectoryName(file);

      itm = new ListViewItem(arr);
      itm.Checked=true ;
      if(InvokeRequired) listView1.Invoke((Action)delegate { listView1.Items.Add(itm); });
      else listView1.Items.Add(itm);

      Application.DoEvents();
    }


    void AddFiles(string[] files)
    {
       foreach (string file in files)
       {
           AddFile(file);
       }
    }

     public static class TextTools
     {
         /// <summary>
         /// delete words in the string.
         /// </summary>
         public static string DeleteWorld(string s, int cnt)
         {
            return Regex.Replace(s, @"\w+", delegate(Match match)
            {
                string v = match.ToString();
                string res = v.Substring(0);
                if (v.Length<cnt) res ="";
                return res;
            });
         }
     }

     string WordsCount(string s, int cnt, char [] punct)
     {
        if (String.IsNullOrWhiteSpace(s)) return s ;
        // 1. ищем все слова, разделенные пунктуацией
        s = TextTools.DeleteWorld(s, cnt) ;
        // 2. удаляем знаки пунктуации
        if (punct.Length>0) {
          for (int i=0;i<punct.Length;i++) {
            string s8 = punct[i].ToString() ;
            s=s.Replace(s8,"");
          }
        }

        // возвращаем строку (модифицированную или нет)
        return s;
     }

    // основная процедура
    // infile  - файл данных
    // outfile - файл результатов
    // int cnt - длина слова для удаления
    // char [] pnct - знаки пунктуации для удаления
    int WorkingFile(string infile,string outfile, int cnt, char [] punct)
    {
       // 1. проверка на сущестование файла
       if (!File.Exists(infile)) {
          AddLogString(" Файл = " + infile + " - не существует. Обработка прервана.");
          return (-1);
       }

       StreamWriter sw = null;
       try
       {
         sw = new StreamWriter(outfile, false, System.Text.Encoding.Default);
       }
       catch (Exception e)
       {
          AddLogString(" Ошибка открытия файла для записи результатов = " + outfile +". Ошибка = " + e.Message);
          AddLogString(" Обработка = " + infile + " - прервана..");
          return(-2);
       }

       using (StreamReader sr = new StreamReader(infile, System.Text.Encoding.Default))
       {
          string line;
          while ((line = sr.ReadLine()) != null)
          {
            string lineS = WordsCount(line, cnt, punct);
            try
            {
                sw.WriteLine(lineS);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
          } // while
       }
       sw.Flush();
       sw.Close();

       AddLogString("\t Обработка = " + infile + " - завершена.");
       AddLogString("\t Файл = "  + outfile + " - создан.");

       return(0) ;
    }




    void ListView1DragDrop(object sender, DragEventArgs e)
    {
         string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
         AddFiles(files) ;
    }
    void ListView1DragEnter(object sender, DragEventArgs e)
    {
         if (e.Data.GetDataPresent(DataFormats.FileDrop, false) == true)
         {
               e.Effect = DragDropEffects.All;
         }
    }
    void Button2Click(object sender, EventArgs e)
    {
        // + добавил файлы по кнопке
          openFileDialog1.Title = "Выберите файл(-ы)";
          openFileDialog1.Filter = "txt файлы|*.txt|All files (*.*)|*.*" ;
          openFileDialog1.FilterIndex =  0;
          openFileDialog1.Multiselect = true ;
          openFileDialog1.FileName = "";
          // выход, если была нажата кнопка Отмена и прочие (кроме ОК)
          if (openFileDialog1.ShowDialog() != DialogResult.OK) return;
          // всё. имя файла теперь хранится в openFileDialog1.FileName
          AddFiles(openFileDialog1.FileNames);
    }
    void Button3Click(object sender, EventArgs e)
    {
      // - удаление файлов из списка
          // нет выделенных файлов
      if (listView1.SelectedItems.Count <= 0) return ;

          int indexSet = 0;
          for (int i = listView1.SelectedItems.Count - 1; i >= 0; i--)
          {
             ListViewItem itm = listView1.SelectedItems[i];
             indexSet = itm.Index ;
             listView1.Items[itm.Index].Remove();
          }
          // устанавливаем фокус
          if (listView1.Items.Count>0) {
            indexSet=0;
            listView1.Items[indexSet].Focused = true;
            listView1.Items[indexSet].Selected = true;
            listView1.Focus();
          }
    }
    void MainFormLoad(object sender, EventArgs e)
    {
           listView1.View = View.Details;
           listView1.GridLines = true;
           listView1.FullRowSelect = true;
           listView1.AllowDrop = true ;

           //Add column header
           listView1.CheckBoxes = true;
           listView1.Columns.Add("Name", 240);
           listView1.Columns.Add("Size (byte)", 90);
           listView1.Columns.Add("*", 80);
           listView1.Columns.Add("Path", 250);
    }
    void Button1Click(object sender, EventArgs e)
    {
      // пользователь нажал на Старт обработки

      // нет выделенных файлов
      if (listView1.CheckedItems.Count <= 0) {
      	AddLogString("  Обработка файлов прервана = не выбраны и не заданы файлы для обработки.");
        return ;
      }

      // создаем массив символов пунктуации
      char [] punct = new char[checkedListBox1.CheckedItems.Count];
      for (int i = checkedListBox1.CheckedItems.Count-1; i >= 0; i--)
      {
        string s1=checkedListBox1.CheckedItems[i].ToString();
        punct[i]=s1.ToCharArray()[0];
      }

      // получаем число символов для удаления
      decimal cntDecimal = numericUpDown1.Value ;
      int cnt = Decimal.ToInt32(cntDecimal);

      // если ничего не задано, обрываем обработку
      if (cnt<=0 && punct.Length<=0) {
        AddLogString("  Обработка файлов прервана = не заданы параметры для обработки ");
        return ;
      }

      AddLogString(" Задана длина символов = " + cnt.ToString());
      string s2 = "" ;
      for(int i = 0; i < punct.Length; i++) s2 = s2 + "  " + punct[i];
      AddLogString(" Заданы знаки пунктуации = " + s2);

      AddLogString(".........Старт обработки");
      // запускаем обработку для каждого файла
      int indexSet;
      for (int i = listView1.CheckedItems.Count - 1; i >= 0; i--)
      {
                ListViewItem itm = listView1.CheckedItems[i];
                indexSet = itm.Index ;

                // формируем имя выходного файла
                DateTime d = DateTime.Now; //
                string frm = "yyyy-MM-dd_HHmmss" ; // Дата = yyyy-MM-dd HH:mm:ss
                string outfiletemp=System.IO.Path.GetFileNameWithoutExtension(itm.SubItems[0].Text) + "_" +
                   d.ToString(frm) + System.IO.Path.GetExtension(itm.SubItems[0].Text);

                // присоединяем Полный Путь
                string infile = System.IO.Path.Combine(itm.SubItems[3].Text, itm.SubItems[0].Text);
                string outfile = System.IO.Path.Combine(itm.SubItems[3].Text, outfiletemp);

                WorkingFile(infile,outfile, cnt, punct);
      }
      AddLogString(".........Конец обработки");

    }


  }
}
