/*
 * Created by SharpDevelop.
 * User: gal
 * Date: 21.06.2016
 * Time: 16:28
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;


namespace test2x
{


	/// <summary>
	/// Description of MainForm.
	/// </summary>
	public partial class MainForm : Form
	{
		
		
	/// <summary>
	/// Description of Bank1.
	/// </summary>
	public class Bank
	{
		// максимальное количество купюр хранимых в Банке.
		// 50 - 100 - 500 - 1000
		public int[] SummaMax={50,30,20,10};
		
		// текущее количество количество купюр хранимых в Банке.
		// 50 - 100 - 500 - 1000		
		public int[] SummaCurr={-1,-1,-1,-1};
		
		public Bank()
		{
		}
		
		public Bank(int cnt50, int cnt100, int cnt500 , int cnt1000)
		{
			this.SummaCurr[0]=cnt50;
			this.SummaCurr[1]=cnt100;
			this.SummaCurr[2]=cnt500;
			this.SummaCurr[3]=cnt1000;

			this.SummaMax[0]=cnt50;
			this.SummaMax[1]=cnt100;
			this.SummaMax[2]=cnt500;
			this.SummaMax[3]=cnt1000;			
		}		
		
		// i - индекс 
		// flag - флаг , true - добавляем
        //               false - снимаем 		
		public int IncrDecr(int i, bool flag)
		{
			if (i<0 || i>3) return(-1) ;
			if (flag) {
				if (this.SummaCurr[i]<SummaMax[i]) { this.SummaCurr[i]=this.SummaCurr[i]+1; }
				else {
				 string message = "Вы превысили лимит по числу купюр.\n Купюра не принята.";
                 string caption = "Системное...";
                 MessageBox.Show(message, caption,
                                 MessageBoxButtons.OK,
                                 MessageBoxIcon.Stop);
                 return(-2);
				}
			} else {
				if (this.SummaCurr[i]>0) { this.SummaCurr[i]=this.SummaCurr[i]-1; }
				else {
				 string message = "Купюр данного номинала больше нет.\n Попробуйте в другой раз.";
                 string caption = "Системное...";
                 MessageBox.Show(message, caption,
                                 MessageBoxButtons.OK,
                                 MessageBoxIcon.Stop);
                 return(-3);
				}				
				
			}
			return(0);
		}		
		
		// i - индекс 
        public int GetCurr(int i)
		{
			if (i<0 || i>3) return(-1) ;
			return(this.SummaCurr[i]);
		}
		
		
	}		
		

		
	    int mode = 1 ; // 1-выдача, 2 - прием;
		
		Bank b1 = new Bank(50,30,20,10);
		
		void Button0Click(int i, string m)
		{
			textBox1.Text="0";
			textBox1.ReadOnly=true;
			button8.Visible=false;
			checkedListBox1.Visible=false;
			if (mode==1) {
				if (0==b1.IncrDecr(i, false)) {
					textBox1.Text=m;
				}
			}
			else {
				if (0==b1.IncrDecr(i, true)) {
					textBox1.Text=m;
				}
			}
		}
		
		
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
		
		
		void MainFormLoad(object sender, EventArgs e)
		{
			
			label50.Text=b1.GetCurr(0).ToString() + " купюр";
			label100.Text=b1.GetCurr(1).ToString() + " купюр";
			label500.Text=b1.GetCurr(2).ToString() + " купюр";
			label1000.Text=b1.GetCurr(3).ToString() + " купюр";
			checkedListBox1.SetItemChecked(0,true);
			checkedListBox1.SetItemChecked(1,true);
			checkedListBox1.SetItemChecked(2,true);
			checkedListBox1.SetItemChecked(3,true);
			Button5Click(sender, e);
	
		} 
		void Button1Click(object sender, EventArgs e)
		{
			Button0Click(0, "50");
			label50.Text=b1.GetCurr(0).ToString() + " купюр";
		}
		void Button2Click(object sender, EventArgs e)
		{
			Button0Click(1, "100");
			label100.Text=b1.GetCurr(1).ToString() + " купюр";	
		}
		void Button3Click(object sender, EventArgs e)
		{
			Button0Click(2, "500");
			label500.Text=b1.GetCurr(2).ToString() + " купюр";	
		}
		void Button4Click(object sender, EventArgs e)
		{
			Button0Click(3, "1000");
			label1000.Text=b1.GetCurr(3).ToString() + " купюр";	
		}
		void Button5Click(object sender, EventArgs e)
		{
			mode=1;
			label3.Text="Режим - Выдача денег";
			button7.Visible=true;
			button8.Visible=false;
			textBox1.ReadOnly=true;
			textBox1.Text="";
			checkedListBox1.Visible=false;
		}
		void Button6Click(object sender, EventArgs e)
		{
			mode=2;
			label3.Text="Режим - Приема денег";
			button7.Visible=false;
			button8.Visible=false;
			textBox1.ReadOnly=true;
			textBox1.Text="";
			checkedListBox1.Visible=false;
		}
		void Button7Click(object sender, EventArgs e)
		{
			textBox1.Text="";
			textBox1.ReadOnly=false;
			button8.Visible=true;
			checkedListBox1.Visible=true;

		}
		void Button8Click(object sender, EventArgs e)
		{
			string message;
			string caption;
			
			string s=textBox1.Text;
			int numValue1=0;
            if (!Int32.TryParse(s, out numValue1)) s="0";
            if (numValue1<=0 || numValue1%50!=0) {
 				 message = "Вводимая сумма должна быть кратна 50 руб.";
                 caption = "Системное...";
                 MessageBox.Show(message, caption,
                                 MessageBoxButtons.OK,
                                 MessageBoxIcon.Stop);  
                 return ;
            }
            textBox1.Text=s;
            
            // Пользователь не отметил ни одну из банкнот
            if (checkedListBox1.GetItemChecked(3)==false &&
                checkedListBox1.GetItemChecked(2)==false &&
                checkedListBox1.GetItemChecked(1)==false &&
                checkedListBox1.GetItemChecked(0)==false) return ;
   
            int sum=numValue1;
            // количество денег для выдачи - 50, 100, 500, 1000
            int [] cntMoney={0,0,0,0};

            // если сумма больше 1000 и пользователь согласился с выдачей 
            if (sum>=1000 && checkedListBox1.GetItemChecked(3)==true) {
            	// проверяем если в Банке купюры
            	int cnt=b1.GetCurr(3);
            	if (cnt>0) {
            		while (sum>=1000 && cnt>0) {
            			cnt=cnt-1;
            			cntMoney[3]=cntMoney[3]+1;
            			sum=sum-1000;
            		}
            	}
            }

            // если сумма больше 500 и пользователь согласился с выдачей 
            if (sum>=500 && checkedListBox1.GetItemChecked(2)==true) {
            	// проверяем если в Банке купюры
            	int cnt=b1.GetCurr(2);
            	if (cnt>0) {
            		while (sum>=500 && cnt>0) {
            			cnt=cnt-1;
            			cntMoney[2]=cntMoney[2]+1;
            			sum=sum-500;
            		}
            	}
            }            

            // если сумма больше 100 и пользователь согласился с выдачей 
            if (sum>=100 && checkedListBox1.GetItemChecked(1)==true) {
            	// проверяем если в Банке купюры
            	int cnt=b1.GetCurr(1);
            	if (cnt>0) {
            		while (sum>=100 && cnt>0) {
            			cnt=cnt-1;
            			cntMoney[1]=cntMoney[1]+1;
            			sum=sum-100;
            		}
            	}
            }            

            // если сумма больше 100 и пользователь согласился с выдачей 
            if (sum>=50 && checkedListBox1.GetItemChecked(0)==true) {
            	// проверяем если в Банке купюры
            	int cnt=b1.GetCurr(0);
            	if (cnt>0) {
            		while (sum>=50 && cnt>0) {
            			cnt=cnt-1;
            			cntMoney[0]=cntMoney[0]+1;
            			sum=sum-50;
            		}
            	}
            } 

            if (sum>0) {
              message = "В банкомате недостаточно средств для выдачи или нет необходимых банкнот.";
              message = message + "\n Обратитесь позже или измените запрашиваемую сумму.";
              message = message + "\n Не хватает до требуемой суммы = " +  sum.ToString() + " рубл.";
              caption = "Системное...";
              MessageBox.Show(message, caption,
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Asterisk); 
              return ;
            }

            message = "Количество выдаваемых банкнот:";
            if (cntMoney[3]>0) message = message + "\n\t 1000 рубл = " + cntMoney[3].ToString() + " шт.";
            if (cntMoney[2]>0) message = message + "\n\t  500 рубл = " + cntMoney[2].ToString() + " шт.";
            if (cntMoney[1]>0) message = message + "\n\t  100 рубл = " + cntMoney[1].ToString() + " шт.";
            if (cntMoney[0]>0) message = message + "\n\t   50 рубл = " + cntMoney[0].ToString() + " шт.";
            message = message + "\n\t  -----------------";
            message = message + "\n\t  Сумма = " + numValue1.ToString() + " рубл";
            caption = "Системное...";
            MessageBox.Show(message, caption,
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);

            // Списываем деньги 
            for (int j=0;j<cntMoney.Length; j++) {
            	while (cntMoney[j]>0) {
            		if (j==0) Button0Click(0, "50");
            		if (j==1) Button0Click(1, "100");
            		if (j==2) Button0Click(2, "500");
            		if (j==3) Button0Click(3, "1000");
            		cntMoney[j]=cntMoney[j]-1;
            	}
            }
            
			label50.Text=b1.GetCurr(0).ToString() + " купюр";
			label100.Text=b1.GetCurr(1).ToString() + " купюр";	
			label500.Text=b1.GetCurr(2).ToString() + " купюр";	
			label1000.Text=b1.GetCurr(3).ToString() + " купюр";	
            
		}
		void TextBox1Enter(object sender, EventArgs e)
		{
	        //Button8Click(sender, e);
		}
	

	}
}
