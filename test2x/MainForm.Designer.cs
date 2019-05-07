/*
 * Created by SharpDevelop.
 * User: gal
 * Date: 21.06.2016
 * Time: 16:28
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace test2x
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Label label50;
		private System.Windows.Forms.Label label100;
		private System.Windows.Forms.Label label500;
		private System.Windows.Forms.Label label1000;
		private System.Windows.Forms.Button button5;
		private System.Windows.Forms.Button button6;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Button button7;
		private System.Windows.Forms.Button button8;
		private System.Windows.Forms.CheckedListBox checkedListBox1;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			this.label1 = new System.Windows.Forms.Label();
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.button4 = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.label50 = new System.Windows.Forms.Label();
			this.label100 = new System.Windows.Forms.Label();
			this.label500 = new System.Windows.Forms.Label();
			this.label1000 = new System.Windows.Forms.Label();
			this.button5 = new System.Windows.Forms.Button();
			this.button6 = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.button7 = new System.Windows.Forms.Button();
			this.button8 = new System.Windows.Forms.Button();
			this.checkedListBox1 = new System.Windows.Forms.CheckedListBox();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.label1.Location = new System.Drawing.Point(230, 117);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(127, 27);
			this.label1.TabIndex = 0;
			this.label1.Text = "Банкомат";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(60, 159);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(166, 44);
			this.button1.TabIndex = 1;
			this.button1.Text = "50  рублей";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.Button1Click);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(61, 223);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(165, 46);
			this.button2.TabIndex = 2;
			this.button2.Text = "100 рублей";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.Button2Click);
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(359, 160);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(149, 43);
			this.button3.TabIndex = 3;
			this.button3.Text = "500 рублей";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new System.EventHandler(this.Button3Click);
			// 
			// button4
			// 
			this.button4.Location = new System.Drawing.Point(357, 224);
			this.button4.Name = "button4";
			this.button4.Size = new System.Drawing.Size(153, 45);
			this.button4.TabIndex = 4;
			this.button4.Text = "1000 рублей";
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Click += new System.EventHandler(this.Button4Click);
			// 
			// label2
			// 
			this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.label2.Location = new System.Drawing.Point(167, 390);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(78, 23);
			this.label2.TabIndex = 6;
			this.label2.Text = "Сумма=";
			// 
			// textBox1
			// 
			this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.textBox1.Location = new System.Drawing.Point(251, 390);
			this.textBox1.Name = "textBox1";
			this.textBox1.ReadOnly = true;
			this.textBox1.Size = new System.Drawing.Size(114, 26);
			this.textBox1.TabIndex = 5;
			this.textBox1.Enter += new System.EventHandler(this.TextBox1Enter);
			// 
			// label50
			// 
			this.label50.Location = new System.Drawing.Point(12, 133);
			this.label50.Name = "label50";
			this.label50.Size = new System.Drawing.Size(109, 23);
			this.label50.TabIndex = 7;
			this.label50.Text = "label50";
			// 
			// label100
			// 
			this.label100.Location = new System.Drawing.Point(13, 277);
			this.label100.Name = "label100";
			this.label100.Size = new System.Drawing.Size(107, 21);
			this.label100.TabIndex = 8;
			this.label100.Text = "label100";
			// 
			// label500
			// 
			this.label500.Location = new System.Drawing.Point(508, 137);
			this.label500.Name = "label500";
			this.label500.Size = new System.Drawing.Size(100, 23);
			this.label500.TabIndex = 9;
			this.label500.Text = "label500";
			// 
			// label1000
			// 
			this.label1000.Location = new System.Drawing.Point(508, 277);
			this.label1000.Name = "label1000";
			this.label1000.Size = new System.Drawing.Size(100, 23);
			this.label1000.TabIndex = 10;
			this.label1000.Text = "label1000";
			// 
			// button5
			// 
			this.button5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.button5.Location = new System.Drawing.Point(597, 86);
			this.button5.Name = "button5";
			this.button5.Size = new System.Drawing.Size(131, 75);
			this.button5.TabIndex = 11;
			this.button5.Text = "Выдача";
			this.button5.UseVisualStyleBackColor = true;
			this.button5.Click += new System.EventHandler(this.Button5Click);
			// 
			// button6
			// 
			this.button6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.button6.Location = new System.Drawing.Point(597, 169);
			this.button6.Name = "button6";
			this.button6.Size = new System.Drawing.Size(131, 85);
			this.button6.TabIndex = 12;
			this.button6.Text = "Прием денег";
			this.button6.UseVisualStyleBackColor = true;
			this.button6.Click += new System.EventHandler(this.Button6Click);
			// 
			// label3
			// 
			this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.label3.ForeColor = System.Drawing.Color.Red;
			this.label3.Location = new System.Drawing.Point(60, 19);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(450, 67);
			this.label3.TabIndex = 13;
			this.label3.Text = "Режим - Выдачи денег";
			this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// label4
			// 
			this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.label4.ForeColor = System.Drawing.Color.Green;
			this.label4.Location = new System.Drawing.Point(597, 19);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(131, 58);
			this.label4.TabIndex = 14;
			this.label4.Text = "Выберите режим работы Банкомата ";
			this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// button7
			// 
			this.button7.Location = new System.Drawing.Point(230, 277);
			this.button7.Name = "button7";
			this.button7.Size = new System.Drawing.Size(119, 44);
			this.button7.TabIndex = 15;
			this.button7.Text = "Другая сумма";
			this.button7.UseVisualStyleBackColor = true;
			this.button7.Click += new System.EventHandler(this.Button7Click);
			// 
			// button8
			// 
			this.button8.Location = new System.Drawing.Point(371, 390);
			this.button8.Name = "button8";
			this.button8.Size = new System.Drawing.Size(92, 23);
			this.button8.TabIndex = 16;
			this.button8.Text = "Принять";
			this.button8.UseVisualStyleBackColor = true;
			this.button8.Click += new System.EventHandler(this.Button8Click);
			// 
			// checkedListBox1
			// 
			this.checkedListBox1.CheckOnClick = true;
			this.checkedListBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.checkedListBox1.FormattingEnabled = true;
			this.checkedListBox1.Items.AddRange(new object[] {
			"50 рубл",
			"100 рубл",
			"500 рубл",
			"1000 рубл"});
			this.checkedListBox1.Location = new System.Drawing.Point(496, 373);
			this.checkedListBox1.Name = "checkedListBox1";
			this.checkedListBox1.Size = new System.Drawing.Size(138, 88);
			this.checkedListBox1.TabIndex = 17;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(740, 490);
			this.Controls.Add(this.checkedListBox1);
			this.Controls.Add(this.button8);
			this.Controls.Add(this.button7);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.button6);
			this.Controls.Add(this.button5);
			this.Controls.Add(this.label1000);
			this.Controls.Add(this.label500);
			this.Controls.Add(this.label100);
			this.Controls.Add(this.label50);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.button4);
			this.Controls.Add(this.button3);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.label1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Name = "MainForm";
			this.Text = "test2x";
			this.Load += new System.EventHandler(this.MainFormLoad);
			this.ResumeLayout(false);
			this.PerformLayout();

		}
	}
}
