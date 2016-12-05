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
///Martix�Ľṹvector< vector <T> >
///T�������������ͻ�С���ͣ�����+��*
///�������һ���վ��󣬵�һ������У����У�������Ӧ����Ԫ����������Ԫ��������ʼ��col(��row)
///һ���ǿվ���������һ�У����У����������У����У��������������������ھ��������������������Զ���ȡ��
///һ���ǿվ���������һ�У����У����������У����У�����������������С�ھ����������������������У��У��Զ�����0��
///1.�ڿվ���g  (row=0, col=0)�� ����
///		����vector<int> a;	//a =100,200,300,400
///		����vector<int> b;	//b =100,200,300,400,500
///		����vector<int> c;	//c =100,200,
///		g.addRow(a);		//g  (row=1, col=4)
///							//g	---> 100,200,300,400	(<-g����գ�col����ʼ��)
///		g.addRow(b);		//g  (row=2, col=4)
///							//g	---> 100,200,300,400	(<-g����գ�col����ʼ��)
///									 100,200,300,400	(<-g����ǿգ���col����ȡ)
///		g.addRow(c);		//g  (row=3, col=4)	
///							//g	---> 100,200,300,400	(<-g����գ�col����ʼ��)
///									 100,200,300,400	(<-g����ǿգ���col����ȡ)
///									 100,200,0,0	    (<-g����ǿգ���col�����)	
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
	//���캯������������
	//���캯����Ϊ�в������޲�����
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

	//�������캯���븳ֵ���غ���
	//�������캯�������ֱ�ӷ�������һ��ͬ��������ã���˽�г�Ա
	//�������������ʼ�������

	Matrix(const Matrix<T> &obj)
	{
		this->m = obj.m;
		this->row = obj.row;
		this->col = obj.col;
	}
	//��ĳ�Ա��������ֱ�ӷ�����Ϊ�������ͬ���Ͷ����˽�г�Ա��
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


	//��_row��λ�ò���_colһ��
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

