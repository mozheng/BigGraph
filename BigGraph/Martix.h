#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;
using std::ostringstream;
using std::istringstream;
using std::runtime_error;

//////////////////////////////////
///Martix的结构vector< vector <T> >
///T建议放入基础类型或小类型，重载+，*
///如果对于一个空矩阵，第一次添加行（或列），所对应的行元素数（或列元素数）初始化col(或row)
///一个非空矩阵，如果添加一行（或列），发现这行（或列）的列数（或行数）大于矩阵列数（或行数）。自动截取。
///一个非空矩阵，如果添加一行（或列），发现这行（或列）的列数（或行数）小于矩阵列数（或行数）。这行（列）自动补充0。
///1.在空矩阵g  (row=0, col=0)中 加入
///		加入vector<int> a;	//a =100,200,300,400
///		加入vector<int> b;	//b =100,200,300,400,500
///		加入vector<int> c;	//c =100,200,
///		g.addRow(a);		//g  (row=1, col=4)
///							//g	---> 100,200,300,400	(<-g矩阵空，col数初始化)
///		g.addRow(b);		//g  (row=2, col=4)
///							//g	---> 100,200,300,400	(<-g矩阵空，col数初始化)
///									 100,200,300,400	(<-g矩阵非空，按col数截取)
///		g.addRow(c);		//g  (row=3, col=4)	
///							//g	---> 100,200,300,400	(<-g矩阵空，col数初始化)
///									 100,200,300,400	(<-g矩阵非空，按col数截取)
///									 100,200,0,0	    (<-g矩阵非空，按col数填充)	
///
/////////////////////
template <class T>
class Matrix {
public:
	typedef vector< vector<T> >	matrix_t;
	typedef vector<T>			matrix_row_t;
	typedef vector<T>			matrix_col_t;

private:
	matrix_t m;
	int row, col;

public:
	int getRow() { return row; }
	int getCol() { return col; }
public:
	//构造函数与析构函数
	//构造函数分为有参数与无参数的
	Matrix(): row(0), col(0){}
	Matrix(int _row, int _col): row(_row), col(_col)
	{
		m.resize(row);
		for (int i = 0; i < row; i++) 
		{
			m[i].resize(i);
		}
	}
	virtual ~Matrix(){}

	//拷贝构造函数与赋值重载函数
	//拷贝构造函数里，可以直接访问另外一个同类对象（引用）的私有成员
	//如果不这样，初始化会出错

	Matrix(const Matrix<T> &obj)
	{
		this->m = obj.m;
		this->row = obj.row;
		this->col = obj.col;
	}
	//类的成员函数可以直接访问作为其参数的同类型对象的私有成员。
	Matrix<T> &operator=(const Matrix<T> &obj)
	{
		if (this != &obj) 
		{
			this->m = obj.m;
			this->row = obj.row;
			this->col = obj.col;
		}
		else
			return *this;

	}


	//在_row的位置插入_col一行
	Martix& insertRow(int _row, matrix_col_t &_col)
		throw(runtime_error)
	{
		if (_row > row ) 
			throw runtime_error("matrix<T>::addRow:: row out-of-bounds");
		m.insert(m.begin() + _row -1 , _col);
		row = row + 1;
		int _col_size = _col.size();
		for (;_col_size < _col;++_col_size)
			m.push_back(0);

		return *this;
	}
	Martix& deleteRow(int _row)
		throw(runtime_error)
	{
		if (_row < 1)
			throw runtime_error("matrix<T>::deleteRow:: row out-of-bounds");
		m.erase(m.begin() + _row);
		row = row - 1;
		return *this;
	}
	void addCol(int _col, matrix_row_t &_row)
		throw(runtime_error)
	{
		if (_col > col)
			throw runtime_error("matrix<T>::addCol:: col out-of-bounds");
		matrix_t tmp;
		tmp.resize(row);
		for (int i = 0; i < row; i++) {
			tmp[i].resize(col + 1);
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < _col; j++) {
				tmp[i][j] = m[i][j];
			}
		}
		for (int j = 0; j < row; j++) {
			tmp[j][_col] = _row[j];
		}
		for (int i = 0; i < row; i++) {
			for (int j = _col + 1, jj = _col; jj < col; j++, jj++) {
				tmp[i][j] = m[i][jj];
			}
		}
		m = tmp;
		col = col + 1;
	}
	void deleteCol(int _col)
	{
		matrix_t tmp;
		tmp.resize(row);
		for (int i = 0; i < row; i++) {
			tmp[i].resize(col - 1);
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < _col; j++) {
				tmp[i][j] = m[i][j];
				
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = _col + 1, jj = _col; j < col; j++, jj++) {
				tmp[i][jj] = m[i][j];
				
			}
		}
		m = tmp;
		col = col - 1;
	}
	// Input/Output.
	friend
		ostream &operator<<(ostream &out, matrix &obj)
	{
		out << " { " << endl;
		for (int i = 0; i < obj.row; i++) {
			for (int j = 0; j < obj.col; j++) {
				if (j == (obj.col - 1)) {
					out << obj.m[i][j] << endl;
				}
				else if (j == 0) {
					out << "   " << obj.m[i][j] << " , ";
				}
				else {
					out << obj.m[i][j] << " , ";
				}
			}
		}
		out << " } " << endl;
		return out;
	}
	string stream_out() const
	{
		ostringstream out;
		out << row << " " << col << " ";
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				out << m[i][j] << " ";
			}
		}
		return out.str();
	}
	void stream_in(string _m)
	{
		istringstream in(_m, istringstream::in);
		in >> row;
		in >> col;
		m.resize(row);
		for (int i = 0; i < row; i++) {
			m[i].resize(col);
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				in >> m[i][j];
			}
		}
	}
	string to_html() const
	{
		ostringstream out;
		out << "<table border=\"1\">" << endl;
		for (int i = 0; i < row; i++) {
			out << "<tr>" << endl;
			for (int j = 0; j < col; j++) {
				out << "<td>" << m[i][j] << "</td>" << endl;
			}
			out << "</tr>" << endl;
		}
		out << "</table>" << endl;
		return out.str();
	}
	// Accessors.
	matrix_t &get_data()
	{
		return m;
	}
	int get_row() const
	{
		return row;
	}
	int get_col() const
	{
		return col;
	}
	matrix_col_t get_row(int _row) const
	{
		matrix_col_t c;
		c.resize(col);
		for (int i = 0; i < col; i++) {
			c[i] = m[_row][i];
		}
		return c;
	}
	matrix_row_t get_col(int _col) const
	{
		matrix_row_t r;
		r.resize(row);
		for (int i = 0; i < row; i++) {
			r[i] = m[i][_col];
		}
		return r;
	}
};

