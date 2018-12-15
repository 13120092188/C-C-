// ComplexSel.cpp : 实现文件
//

#include "stdafx.h"
#include "DBMS.h"
#include "ComplexSel.h"
#include "afxdialogex.h"

#pragma warning(disable:4996)
// CComplexSel 对话框

IMPLEMENT_DYNAMIC(CComplexSel, CDialogEx)

CComplexSel::CComplexSel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComplexSel::IDD, pParent)
{

}

CComplexSel::~CComplexSel()
{
}

void CComplexSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CONTENT_EDIT, edit_content);
}


BEGIN_MESSAGE_MAP(CComplexSel, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CComplexSel::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_OK_BUTTON, &CComplexSel::OnBnClickedOkButton)
	ON_BN_CLICKED(IDCANCEL, &CComplexSel::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_TABLE_COMBO, &CComplexSel::OnCbnSelchangeTableCombo)
	ON_CBN_SELCHANGE(IDC_FIELD_COMBO, &CComplexSel::OnCbnSelchangeFieldCombo)
END_MESSAGE_MAP()


// CComplexSel 消息处理程序


void CComplexSel::OnBnClickedAddButton()
{
	// TODO:  在此添加控件通知处理程序代码
	CString select_table;
	((CComboBox *)GetDlgItem(IDC_TABLE_COMBO))->GetLBText(((CComboBox *)GetDlgItem(IDC_TABLE_COMBO))->GetCurSel(), select_table);

	int len = WideCharToMultiByte(CP_ACP, 0, select_table, -1, NULL, 0, NULL, NULL);
	char *get_table = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, select_table, -1, get_table, len, NULL, NULL);

	CString select_field;
	((CComboBox *)GetDlgItem(IDC_FIELD_COMBO))->GetLBText(((CComboBox *)GetDlgItem(IDC_FIELD_COMBO))->GetCurSel(), select_field);

	len = WideCharToMultiByte(CP_ACP, 0, select_field, -1, NULL, 0, NULL, NULL);
	char *get_field = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, select_field, -1, get_field, len, NULL, NULL);

	table *tab = new table;
	strcpy(tab->table_name, get_table);


	if (t == NULL){
		t = tab;
		table_num++;
	}
	else{
		BOOL judge = TRUE;
		table *p = t;

		while (true){
			if (strcmp(p->table_name, get_table) == 0){
				judge = FALSE;
				break;
			}
			if (p->next == NULL){
				break;
			}
			else{
				p = p->next;
			}
		}
		if (judge == TRUE){
			p->next = tab;
			table_num++;
		}
	}

	if (field_num == 0){
		strcpy(f[field_num].table_name, get_table);
		strcpy(f[field_num].field_name, get_field);
		field_num++;
	}
	else{
		int sign = 0;
		for (int i = 0; i < field_num; i++){
			if (strcmp(f[i].table_name, get_table) == 0 && strcmp(f[i].field_name, get_field) == 0){
				sign = 1;
				break;
			}
		}
		if (sign == 0){
			strcpy(f[field_num].table_name, get_table);
			strcpy(f[field_num].field_name, get_field);
			field_num++;
		}
	}
	MessageBox(L"字段添加成功！");
}


void CComplexSel::OnBnClickedOkButton()
{
	// TODO:  在此添加控件通知处理程序代码
	table *p = t;
	int select_num = 1;
	for (int i = 0; i < table_num; i++){
		string tab_address = p->table_name;
		tab_address = tab_address + "_s.txt";
		ifstream read_table(tab_address);

		int n = 0;
		read_table >> n;
		p->field_num = n;

		for (int j = 0; j < n; j++){
			char content[20];
			read_table >> content;
			strcpy(p->field_name[j], content);
		}
		read_table.close();

		string data_address = p->table_name;
		data_address = data_address + "_d.txt";
		ifstream read_data(data_address);

		int m = 0;
		char num[3];
		read_data.getline(num, sizeof(num));
		m = atoi(num);
		p->row_num = m;

		for (int i = 0; i < m; i++){
			for (int k = 0; k < n; k++){
				char content[10];
				read_data.getline(content, sizeof(content));
				strcpy(p->r[i].field_value[k], content);
			}
		}
		read_data.close();

		select_num = select_num * m;
		p = p->next;
	}

	int *pass = new int[select_num];
	memset(pass, 0, sizeof(int)* select_num);

	//筛选
	CString conditions;
	((CEdit *)GetDlgItem(IDC_CONDITION_EDIT))->GetWindowTextW(conditions);

	int len = WideCharToMultiByte(CP_ACP, 0, conditions, -1, NULL, 0, NULL, NULL);
	char *get_condition = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, conditions, -1, get_condition, len, NULL, NULL);

	const char *space = " ";
	const char *point = ".";
	const char *equal = "=";
	const char *less = "<";
	const char *greater = ">";

	char *con;
	condition c[10];
	con = strtok(get_condition, space);
	int count_condition = 0;
	while (con){
		strcpy(c[count_condition].content, con);
		con = strtok(NULL, space);
		count_condition++;
	}
	free(con);

	for (int i = 0; i < count_condition; i++){
		char str[100];
		strcpy(str, c[i].content);
		char *a;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (strstr(str, equal) != NULL){

			a = strtok(str, equal);
			char left[20];
			char right[20];
			strcpy(left, a);
			a = strtok(NULL, equal);
			strcpy(right, a);

			char *b;
			b = strtok(left, point);
			strcpy(c[i].left.table_name, b);
			b = strtok(NULL, point);
			strcpy(c[i].left.field_name, b);

			if (strstr(right, ".") == NULL){
				table *m = t;
				condition_equal(m, 1, c[i].left.table_name, c[i].left.field_name, right, "", 0);
			}
			else{
				table *m = t;
				strcpy(equal_field[equal_condition_count].table_name, c[i].left.table_name);
				strcpy(equal_field[equal_condition_count].field_name, c[i].left.field_name);
				condition_equal(m, 2, c[i].left.table_name, c[i].left.field_name, right, "", 0);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (strstr(str, less) != NULL){

			a = strtok(str, less);
			char left[20];
			char right[20];
			strcpy(left, a);
			a = strtok(NULL, less);
			strcpy(right, a);

			char *b;
			b = strtok(left, point);
			strcpy(c[i].left.table_name, b);
			b = strtok(NULL, point);
			strcpy(c[i].left.field_name, b);

			table *m = t;
			condition_less(m, c[i].left.table_name, c[i].left.field_name, right);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (strstr(str, greater) != NULL){

			a = strtok(str, greater);
			char left[20];
			char right[20];
			strcpy(left, a);
			a = strtok(NULL, greater);
			strcpy(right, a);

			char *b;
			b = strtok(left, point);
			strcpy(c[i].left.table_name, b);
			b = strtok(NULL, point);
			strcpy(c[i].left.field_name, b);

			table *m = t;
			condition_greater(m, c[i].left.table_name, c[i].left.field_name, right);
		}
	}


	//输出
	char *s = "";
	table *m = t;
	int x = 0;
	output(s, m, 0);

	ifstream in("output.txt", std::ios::binary);
	int length;
	in.seekg(0, std::ios::end);
	length = in.tellg();
	in.seekg(0, std::ios::beg);
	char *buffer = new char[length + 1];
	in.read(buffer, length);
	in.close();

	edit_content = buffer;
	UpdateData(FALSE);

	ofstream cover("output.txt");
	cover << "";
	cover.close();
}


void CComplexSel::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CComplexSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ifstream read_table("tablelist.txt");

	int n = 0;
	char num[3];
	read_table.getline(num, sizeof(num));

	n = atoi(num);

	for (int i = 0; i < n; i++){
		char content[10];
		read_table.getline(content, sizeof(content));
		CString c(content);

		((CComboBox *)GetDlgItem(IDC_TABLE_COMBO))->AddString(c);
	}
	read_table.close();

	field_num = 0;
	table_num = 0;
	t = NULL;
	equal_condition_count = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CComplexSel::OnCbnSelchangeTableCombo()
{
	// TODO:  在此添加控件通知处理程序代码
	CString select;

	((CComboBox *)GetDlgItem(IDC_TABLE_COMBO))->GetLBText(((CComboBox *)GetDlgItem(IDC_TABLE_COMBO))->GetCurSel(), select);

	select = select + _T("_s.txt");

	int len = WideCharToMultiByte(CP_ACP, 0, select, -1, NULL, 0, NULL, NULL);
	char *address = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, select, -1, address, len, NULL, NULL);

	ifstream read_table(address);

	int n = 0;
	char num[3];
	read_table.getline(num, sizeof(num));
	n = atoi(num);
	((CComboBox *)GetDlgItem(IDC_FIELD_COMBO))->ResetContent();

	for (int i = 0; i < n; i++){
		char content[10];
		read_table.getline(content, sizeof(content));
		CString c(content);

		((CComboBox *)GetDlgItem(IDC_FIELD_COMBO))->AddString(c);
	}

	read_table.close();
	delete[] address;
}


void CComplexSel::OnCbnSelchangeFieldCombo()
{
	// TODO:  在此添加控件通知处理程序代码
}
void CComplexSel::output(char *sstr, table *tab, int index){
	if (table_num == 1){
		char *space = " ";
		for (int i = 0; i < tab->row_num; i++){

			char str[100];
			strcpy(str, sstr);
			for (int j = 0; j < tab->field_num; j++){
				for (int k = 0; k < field_num; k++){
					if (strcmp(f[k].field_name, tab->field_name[j]) == 0 && strcmp(f[k].table_name, tab->table_name) == 0){
						strcat(str, tab->r[i].field_value[j]);
						strcat(str, space);
					}
				}
			}
			if (tab->judge_a[i] == 0){
				fstream out("output.txt", ios::app);
				out << str << endl;
				out.close();
			}
		}
	}
	else{
		char *space = " ";
		for (int i = 0; i < tab->row_num; i++){

			for (int j = 0; j < equal_condition_count; j++){
				if (strcmp(tab->table_name, equal_field[j].table_name) == 0){
					equal_field[j].row_num = i;
				}
				if (strcmp(tab->table_name, equal_field[j].table_name_opposite) == 0){
					equal_field[j].row_num_opposite = i;
				}
			}

			char str[10000];
			strcpy(str, sstr);
			for (int j = 0; j < tab->field_num; j++){
				for (int k = 0; k < field_num; k++){
					if (strcmp(f[k].field_name, tab->field_name[j]) == 0 && strcmp(f[k].table_name, tab->table_name) == 0){
						strcat(str, tab->r[i].field_value[j]);
						strcat(str, space);
					}
				}
			}
			if (tab->next != NULL && tab->judge_a[i] == 0){
				output(str, tab->next, tab->judge_b[i]);
			}

			if (equal_condition_count > 0){

				int count = 0;
				for (int j = 0; j < equal_condition_count; j++){
					table *p = t;
					table *q = t;
					while (strcmp(p->table_name, equal_field[j].table_name) != 0){
						p = p->next;
					}
					while (strcmp(q->table_name, equal_field[j].table_name_opposite) != 0){
						q = q->next;
					}
					if (strcmp(p->r[equal_field[j].row_num].field_value[equal_field[j].field_position], q->r[equal_field[j].row_num_opposite].field_value[equal_field[j].field_position_opposite]) == 0){
						count++;
					}
				}
				if (count == equal_condition_count){
					if (tab->judge_a[i] == 0){
						if (tab->next == NULL){
							fstream out("output.txt", ios::app);
							out << str << endl;
							out.close();
						}
					}
				}
			}
			else{
				if (tab->judge_a[i] == 0){
					if (tab->next == NULL){
						fstream out("output.txt", ios::app);
						out << str << endl;
						out.close();
					}
				}
			}

		}
	}
}

void CComplexSel::condition_equal(table *tab, int sign, char *table_name, char *field, char *right, char *sp, int index){

	if (sign == 1){
		for (int i = 0; i < tab->row_num; i++){
			for (int j = 0; j < tab->field_num; j++){
				if (strcmp(field, tab->field_name[j]) == 0 && strcmp(table_name, tab->table_name) == 0){
					if (strcmp(tab->r[i].field_value[j], right) != 0 && sp == ""){
						tab->judge_a[i] = 1;
					}
				}
			}
			if (tab->next != NULL/* && sp == ""*/){
				condition_equal(tab->next, 1, table_name, field, right, sp, 0);
			}
			/*	else if (tab->next != NULL && sp != ""){
			condition_equal(tab->next, 1, table_name, field, right, sp, index);
			}*/
		}
	}
	else{

		char *d;
		char table_name[20];
		char field_name[20];
		char new_right[20];
		strcpy(new_right, right);
		d = strtok(new_right, ".");
		strcpy(table_name, d);
		d = strtok(NULL, ".");
		strcpy(field_name, d);

		strcpy(equal_field[equal_condition_count].table_name_opposite, table_name);
		strcpy(equal_field[equal_condition_count].field_name_opposite, field_name);


		table *table_list = t;
		while (strcmp(table_list->table_name, equal_field[equal_condition_count].table_name) != 0){
			table_list = table_list->next;
		}
		for (int i = 0; i < table_list->field_num; i++){
			if (strcmp(table_list->field_name[i], equal_field[equal_condition_count].field_name) == 0){
				equal_field[equal_condition_count].field_position = i;
				break;
			}
		}


		table_list = t;
		while (strcmp(table_list->table_name, equal_field[equal_condition_count].table_name_opposite) != 0){
			table_list = table_list->next;
		}
		for (int i = 0; i < table_list->field_num; i++){
			if (strcmp(table_list->field_name[i], equal_field[equal_condition_count].field_name_opposite) == 0){
				equal_field[equal_condition_count].field_position_opposite = i;
				break;
			}
		}

		equal_condition_count++;

		/*	char *r;
		for (int i = 0; i < tab->row_num; i++){
		for (int j = 0; j < tab->field_num; j++){
		if (strcmp(table_name, tab->table_name) == 0 && strcmp(field, tab->field_name[j]) == 0){
		r = tab->r[i].field_value[j];
		tab->judge_b[i] = i;
		}
		}
		if (tab->next != NULL){
		condition_equal(tab->next, 1, table_name, field_name, right,r,i);
		}
		}*/
	}
}

void CComplexSel::condition_greater(table *tab, char *table, char *field, char *right){

	for (int i = 0; i < tab->row_num; i++){
		for (int j = 0; j < tab->field_num; j++){
			if (strcmp(field, tab->field_name[j]) == 0 && strcmp(table, tab->table_name) == 0){
				int l = atoi(tab->r[i].field_value[j]);
				int r = atoi(right);
				if (l<r){
					tab->judge_a[i] = 1;
				}
			}
		}
		if (tab->next != NULL){
			condition_greater(tab->next, table, field, right);
		}
	}
}

void CComplexSel::condition_less(table *tab, char *table, char *field, char *right){

	for (int i = 0; i < tab->row_num; i++){
		for (int j = 0; j < tab->field_num; j++){
			if (strcmp(field, tab->field_name[j]) == 0 && strcmp(table, tab->table_name) == 0){
				int l = atoi(tab->r[i].field_value[j]);
				int r = atoi(right);
				if (l>r){
					tab->judge_a[i] = 1;
				}
			}
		}
		if (tab->next != NULL){
			condition_less(tab->next, table, field, right);
		}
	}
}