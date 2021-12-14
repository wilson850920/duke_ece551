#include "IntMatrix.h"

IntMatrix::IntMatrix(): numRows(0), numColumns(0), rows(NULL){
}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c){
	rows = new IntArray *[numRows];
	for (int i = 0; i < numRows; i ++){
	       rows[i] = new IntArray(numColumns); 
	}
}

IntMatrix::IntMatrix(const IntMatrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns){
       	rows = new IntArray *[rhs.numRows];
	for (int k = 0; k < rhs.numRows; k ++){
		rows[k] = new IntArray(numColumns);
		*rows[k] = *rhs.rows[k];
	}
}

IntMatrix::~IntMatrix() {
	for (int k = 0; k < numRows; k ++){
		delete rows[k];
	}
	delete[] rows;
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
	if (this != &rhs){
		IntArray ** temp = new IntArray * [rhs.numRows];
		for (int i = 0; i < rhs.numRows; i ++){
			temp[i] = new IntArray(rhs.numColumns);
			*temp[i] = *rhs.rows[i];
		}
		for ( int i = 0; i < numRows; i ++){
			delete rows[i];
		}
		delete[] rows;
		rows = temp;
		numRows = rhs.numRows;
		numColumns = rhs.numColumns;
	}
	return * this;
}

int IntMatrix::getRows() const {
	return numRows;
}

int IntMatrix::getColumns() const {
	return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
	assert(0 <= index && index < numRows);
	return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
	assert(0 <= index && index < numRows);
	return *rows[index];
}



bool IntMatrix::operator==(const IntMatrix & rhs) const {
	if ((numRows != rhs.numRows) || (numColumns != rhs.numColumns)){
		return false;
	}
	for (int k = 0; k < rhs.numRows; k ++){
		if (*rows[k] != *rhs.rows[k]){
			return false;
		}
	}
	return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
	assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
	IntMatrix ans(numRows, numColumns);
	for (int i = 0; i < rhs.numRows; i++) {
		for (int j = 0; j < numColumns; j++) {
			(*ans.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
		}
	}
	return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
	s << "[ ";
	for (int i = 0; i < rhs.getRows(); i ++){
		s << rhs[i];
		if (i != rhs.getRows() - 1){
			s << "," << std::endl;
		}
	}
	s << " ]";
	return s;
}
