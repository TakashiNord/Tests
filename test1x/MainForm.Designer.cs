/*
 * Created by SharpDevelop.
 * User: gal
 * Date: 21.06.2016
 * Time: 9:11
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace test1x
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		private System.Windows.Forms.RichTextBox richTextBox1;
		private System.Windows.Forms.ListView listView1;
		private System.Windows.Forms.NumericUpDown numericUpDown1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.CheckedListBox checkedListBox1;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		
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
			this.richTextBox1 = new System.Windows.Forms.RichTextBox();
			this.listView1 = new System.Windows.Forms.ListView();
			this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.checkedListBox1 = new System.Windows.Forms.CheckedListBox();
			this.label3 = new System.Windows.Forms.Label();
			this.button1 = new System.Windows.Forms.Button();
			this.label4 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.button2 = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
			this.SuspendLayout();
			// 
			// richTextBox1
			// 
			this.richTextBox1.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.richTextBox1.Location = new System.Drawing.Point(0, 390);
			this.richTextBox1.Name = "richTextBox1";
			this.richTextBox1.Size = new System.Drawing.Size(715, 137);
			this.richTextBox1.TabIndex = 0;
			this.richTextBox1.Text = "";
			// 
			// listView1
			// 
			this.listView1.CheckBoxes = true;
			this.listView1.Location = new System.Drawing.Point(0, 0);
			this.listView1.Name = "listView1";
			this.listView1.Size = new System.Drawing.Size(451, 384);
			this.listView1.TabIndex = 1;
			this.listView1.UseCompatibleStateImageBehavior = false;
			this.listView1.DragDrop += new System.Windows.Forms.DragEventHandler(this.ListView1DragDrop);
			this.listView1.DragEnter += new System.Windows.Forms.DragEventHandler(this.ListView1DragEnter);
			// 
			// numericUpDown1
			// 
			this.numericUpDown1.Location = new System.Drawing.Point(514, 77);
			this.numericUpDown1.Name = "numericUpDown1";
			this.numericUpDown1.Size = new System.Drawing.Size(60, 20);
			this.numericUpDown1.TabIndex = 2;
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(464, 58);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(161, 16);
			this.label1.TabIndex = 3;
			this.label1.Text = "Удаление слов длиной менее ";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(580, 79);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(60, 17);
			this.label2.TabIndex = 4;
			this.label2.Text = "символов";
			// 
			// checkedListBox1
			// 
			this.checkedListBox1.CheckOnClick = true;
			this.checkedListBox1.FormattingEnabled = true;
			this.checkedListBox1.Items.AddRange(new object[] {
			"\'",
			"[",
			"]",
			"( ",
			")",
			"{",
			"} ",
			":",
			",",
			"—",
			"!",
			".",
			"?",
			"“",
			"«",
			"»",
			";",
			"/"});
			this.checkedListBox1.Location = new System.Drawing.Point(464, 127);
			this.checkedListBox1.MultiColumn = true;
			this.checkedListBox1.Name = "checkedListBox1";
			this.checkedListBox1.Size = new System.Drawing.Size(245, 169);
			this.checkedListBox1.TabIndex = 5;
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(464, 109);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(161, 15);
			this.label3.TabIndex = 6;
			this.label3.Text = "Удаление знаков пунктуации";
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(634, 311);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 72);
			this.button1.TabIndex = 7;
			this.button1.Text = "Запуск обработки файлов";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.Button1Click);
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(457, 332);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(171, 51);
			this.label4.TabIndex = 8;
			this.label4.Text = "После обработки файла, создается новый  по шаблону <старое_имя>_<дата>";
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(457, 311);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(100, 21);
			this.label5.TabIndex = 9;
			this.label5.Text = "Внимание";
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(481, 4);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(93, 41);
			this.button2.TabIndex = 10;
			this.button2.Text = "Добавить Файл в список";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.Button2Click);
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(605, 4);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(93, 41);
			this.button3.TabIndex = 11;
			this.button3.Text = "Удалить из Списка";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new System.EventHandler(this.Button3Click);
			// 
			// openFileDialog1
			// 
			this.openFileDialog1.FileName = "openFileDialog1";
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(715, 527);
			this.Controls.Add(this.button3);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.checkedListBox1);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.numericUpDown1);
			this.Controls.Add(this.listView1);
			this.Controls.Add(this.richTextBox1);
			this.Name = "MainForm";
			this.Text = "test1x";
			this.Load += new System.EventHandler(this.MainFormLoad);
			((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
			this.ResumeLayout(false);

		}
	}
}
