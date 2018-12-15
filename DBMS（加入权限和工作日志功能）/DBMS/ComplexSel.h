#pragma once
#include <fstream>

using namespace std;

#pragma once

class field_select{
public:
	field_select(){
		memset(table_name, 0, sizeof(char)* 10);
		memset(field_name, 0, sizeof(char)* 10);
		field_position = 0;
		row_num = 0;
		row_num_opposite = 0;
	}
	char table_name[10];
	char field_name[10];
	int field_position;
	int row_num;
	char table_name_opposite[10];
	char field_name_opposite[10];
	int field_position_opposite;
	int row_num_opposite;
};

class condition{
public:
	condition(){
		memset(content, 0, sizeof(char)* 100);
	}
	char content[100];
	field_select left;
	field_select right;
};

class row{
public:
	row(){
		memset(field_value, 0, sizeof(field_value));
	}
	char field_value[20][20];
};

class table{
public:
	table(){
		next = NULL;
		memset(field_name, 0, sizeof(field_name));
		memset(judge_a, 0, sizeof(field_name));
		memset(judge_b, 0, sizeof(field_name));
		field_num = 0;
		row_num = 0;
	}
	char table_name[10];
	char field_name[20][20];
	int judge_a[20];
	int judge_b[20];
	int field_num;
	int row_num;
	row r[20];
	table *next;
};


// CComplexSel 对话框

class CComplexSel : public CDialogEx
{
	DECLARE_DYNAMIC(CComplexSel)

public:
	CComplexSel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CComplexSel();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedOkButton();
	afx_msg void OnBnClickedCancel();
	int field_num;
	int table_num;
	int equal_condition_count;
	field_select f[10];
	field_select equal_field[10];

	table *t;

	void output(char *sstr, table *tab, int index);
	void condition_equal(table *tab, int signchar, char *table, char *field, char *right, char *sp, int index);
	void condition_greater(table *tab, char *table, char *field, char *right);
	void condition_less(table *tab, char *table, char *field, char *right);

	CString edit_content;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeTableCombo();
	afx_msg void OnCbnSelchangeFieldCombo();
};
