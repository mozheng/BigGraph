#pragma once
#include <vector>
#include <iterator>


using std::vector;
using std::string;

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
	//在末尾添加一行
	Matrix& addRow(matrix_row_t &vector_row)
	{
		int vector_row_size = vector_row.size();
		if (vector_row_size == 0)return *this;
		if (row == 0)
		{
			m.push_back(vector_row);
			col = vector_row_size;
		}
		else
		{
			if (vector_row_size != col)
				vector_row.resize(col);
			m.push_back(vector_row);
		}
		++row;
		return *this;
	}

	//在_row的位置插入vector_row一行
	Matrix& insertRow(int _row, matrix_row_t & vector_row)
		throw(runtime_error)
	{
		//零矩阵插入时进入添加模式
		if (_row == row &&row == 0)
			return addRow(vector_row);

		//越界添加报异常
		if (_row > row || _row < 1)
			throw runtime_error("matrix<T>::addRow:: row out-of-bounds");
		//插入为空直接返回
		int vector_row_size = vector_row.size();
		if (vector_row_size == 0)return *this;


		if (vector_row_size ！ = col)
			vector_row.resize(col);
		m.insert(m.begin() + _row - 1, vector_row);
		++row;
		return *this;
	}

	//在_row的位置删除一行
	//删成空矩阵时col设为0
	Matrix& deleteRow(int _row)
		throw(runtime_error)
	{
		//越界添加报异常
		if (_row < 1 || _row > row)
			throw runtime_error("matrix<T>::deleteRow:: row out-of-bounds");
		m.erase(m.begin() + _row -1);
		--row;
		if (row == 0)
			col = 0;
		return *this;
	}

	////////////////////////////////////////////////////
	///下面是列操作
	//在末尾添加一列
	Matrix& addcol(matrix_col_t &vector_col)
	{
		int vector_col_size = vector_col.size();
		if (vector_col_size == 0)return *this;
		if (col == 0)
		{
			m.resize(vector_col_size);
			for (int i = 0; i < vector_col_size; ++i)
				m[i].push_back(vector_col[i]);
			row = vector_col_size;
		}
		else
		{
			if (vector_col_size != row)
				vector_col.resize(row);
			for (int i = 0; i < vector_col_size; ++i)
				m[i].push_back(vector_col[i]);
		}
		++col;
		return *this;
	}

	//在_col的位置插入vector_col一行
	Matrix& insertCol(int _col, matrix_col_t & vector_col)
		throw(runtime_error)
	{
		//零矩阵插入时进入添加模式
		if (_col == col &&col == 0)
			return addCol(vector_col);
		//越界添加报异常
		if (_col > col || col < 1)
			throw runtime_error("matrix<T>::insertCol:: col out-of-bounds");
		int vector_col_size = vector_col.size();
		if (vector_col_size == 0)return *this;

		if (vector_col_size ！ = row)
			vector_col.resize(row);
		for (int i = 0; i < row; ++i)
			m[i].push_back(vector_col[i]);
		++col;
		return *this;

	}
	//在_col的位置删除一行
	//删成空矩阵时row设为0
	Matrix& deleteCol(int _col)
	{
		//越界添加报异常
		if (_col < 1 || _col > col)
			throw runtime_error("matrix<T>::deleteCol:: col out-of-bounds");
		
		for (vector< vector<T> >::iterator it = m.begin(); it != m.end(); ++it)
			it->erase((it->begin()) + _col - 1);
		--col;
		if (col == 0)
		{
			m.resize(0);
			row = 0;
		}
		return *this;
	}





	matrix_t& getMatix()
	{
		return m;
	}
	int getRowSize() const
	{
		return row;
	}
	int getColSize() const
	{
		return col;
	}
	matrix_col_t getRow(int _row) const
	{
		matrix_col_t c;
		c.resize(col);
		for (int i = 0; i < col; i++)
			c[i] = m[_row][i];
		return c;
	}
	matrix_row_t getCol(int _col) const
	{
		matrix_row_t r;
		r.resize(row);
		for (int i = 0; i < row; i++)
			r[i] = m[i][_col];
		return r;
	}
};

