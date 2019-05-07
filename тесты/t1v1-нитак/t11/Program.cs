/*
 * Created by SharpDevelop.
 * User: gal
 * Date: 21.06.2016
 * Time: 11:42
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Text.RegularExpressions;

using System.Collections.Generic;
using System.Linq;

namespace t11
{
	class Program
	{

	   static string WordsCount(string s, int cnt, char [] punct)
       {
	   	if (String.IsNullOrWhiteSpace(s)) return s ;
        // ищем все слова, разделенные пунктуацией
	   	string pattern = @"\w+";
        Regex regex = new Regex(pattern);
        MatchCollection matches = regex.Matches(s) ;
       	int n = matches.Count ;
       	// 1. удаляем слова
       	if (n>0) {
           	// создаем список слов для удаления 
       		List<string> strWords = new List<string>();
       	    foreach (Match match in matches)
            {
        	   string s1 = match.Groups[0].Value ;
        	   // если длина слова менее .. символов, добавляем в список для удаления
        	   if (s1.Length<cnt) {
        		   strWords.Add(s1);
        	   }
            }
       	    if (strWords.Capacity>0) {
       	    	// сортируем список слов для удаления в порядке убывания длины
       	    	// сначала  мы должны удалить самое длинное слово а далее по уменьшению
      	    	List<string> strWordsSorted =   
                  (from t in strWords orderby t.Length descending select t)  
                        .ToList<string>();  
      	    	// удаляем
                foreach (string st in strWordsSorted)
                {
        	       s=s.Replace(st,"");
                }    
                strWordsSorted.Clear();
       	    }
       	    strWords.Clear();
       	}
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
    static int WorkingFile(string infile,string outfile, int cnt, char [] punct)
    {
    	
       // 1. проверка на сущестование файла
       if (!File.Exists(infile)) return (-1);

       StreamWriter sw = null;
       try
       {
         sw = new StreamWriter(outfile, false, System.Text.Encoding.Default);
       }
       catch (Exception e)
       {
       	return (-2);
       }
    
       using (StreamReader sr = new StreamReader(infile, System.Text.Encoding.Default))
       {
 	      string line;
          while ((line = sr.ReadLine()) != null)
          {
         	string lineS = WordsCount(line, cnt, punct);
         	Console.WriteLine(lineS);
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
       
       return(0) ;
    }  


		public static void Main(string[] args)
		{
			Console.WriteLine("Hello World!");
			
			// TODO: Implement Functionality Here
			string path="text.txt";
			string path1="text.log";
			char[] splitter = new char[] { ';', '.', ',', '!', '?', '-' };
			
			int res=WorkingFile(path, path1, 4, splitter) ;
			if (res==-1)
				Console.WriteLine("\t" + path + " not exists. Unchecked.");
			if (res==-2)
				Console.WriteLine("\t" + path1 + " cannot create. ");	
		    if (res==0)
				Console.WriteLine("\t File " + path1 + " - created. ");
			
			Console.Write("Press any key to continue . . . ");
			Console.ReadKey(true);
		}
	}
}