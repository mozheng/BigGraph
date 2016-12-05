#pragma once
#include <vector>
#include <iterator>


using std::vector;
using std::string;

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
	//��ĩβ���һ��
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

	//��_row��λ�ò���vector_rowһ��
	Matrix& insertRow(int _row, matrix_row_t & vector_row)
		throw(runtime_error)
	{
		//��������ʱ�������ģʽ
		if (_row == row &&row == 0)
			return addRow(vector_row);

		//Խ����ӱ��쳣
		if (_row > row || _row < 1)
			throw runtime_error("matrix<T>::addRow:: row out-of-bounds");
		//����Ϊ��ֱ�ӷ���
		int vector_row_size = vector_row.size();
		if (vector_row_size == 0)return *this;


		if (vector_row_size �� = col)
			vector_row.resize(col);
		m.insert(m.begin() + _row - 1, vector_row);
		++row;
		return *this;
	}

	//��_row��λ��ɾ��һ��
	//ɾ�ɿվ���ʱcol��Ϊ0
	Matrix& deleteRow(int _row)
		throw(runtime_error)
	{
		//Խ����ӱ��쳣
		if (_row < 1 || _row > row)
			throw runtime_error("matrix<T>::deleteRow:: row out-of-bounds");
		m.erase(m.begin() + _row -1);
		--row;
		if (row == 0)
			col = 0;
		return *this;
	}

	////////////////////////////////////////////////////
	///�������в���
	//��ĩβ���һ��
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

	//��_col��λ�ò���vector_colһ��
	Matrix& insertCol(int _col, matrix_col_t & vector_col)
		throw(runtime_error)
	{
		//��������ʱ�������ģʽ
		if (_col == col &&col == 0)
			return addCol(vector_col);
		//Խ����ӱ��쳣
		if (_col > col || col < 1)
			throw runtime_error("matrix<T>::insertCol:: col out-of-bounds");
		int vector_col_size = vector_col.size();
		if (vector_col_size == 0)return *this;

		if (vector_col_size �� = row)
			vector_col.resize(row);
		for (int i = 0; i < row; ++i)
			m[i].push_back(vector_col[i]);
		++col;
		return *this;

	}
	//��_col��λ��ɾ��һ��
	//ɾ�ɿվ���ʱrow��Ϊ0
	Matrix& deleteCol(int _col)
	{
		//Խ����ӱ��쳣
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

