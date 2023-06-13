//Quad tree is a tree data structure in which each internal node has exactly four children :
//north - west(NW), north - east(NE), south - west(SW), and south - east(SE).Each node
//represents a quadrant in a two - dimensional space.This data structure is used to recursively
//divide a two - dimensional space into four quadrants until each quadrant contains only one
//element.In this case, the elements are the pixels in the image.The quad tree is constructed
//by dividing the image into four quadrants, and recursively applying the same process to
//each quadrant until each quadrant contains only one pixel.

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

class LLNode {
public:
	LLNode* next;
	LLNode* down;
	int value;
	LLNode() {
		next = NULL;
		down = NULL;
		value = 0;
	}
	LLNode(int val) {
		next = NULL;
		down = NULL;
		value = val;
	}
};

class TwoDLL {
public:
	LLNode* head;
public:
	TwoDLL() {
		head = NULL;
	}

	TwoDLL(LLNode* node) {
		head = node;
	}

	void convertTo2dLL(int** array, int row, int col) {
		if (head == NULL) {
			bool color_continue = false;
			LLNode* curr_row_head = NULL;
			LLNode* curr_row_node = NULL;

			for (int i = 0; i < row; i++) {
				if (i == 0) {
					head = new LLNode;
					head->value = i + 1;
					curr_row_head = head;
				}
				else {
					curr_row_head->down = new LLNode;
					curr_row_head = curr_row_head->down;
					curr_row_head->value = i + 1;
				}
				curr_row_node = curr_row_head;
				// for traversal of white color
				for (int j = 0; j < col; j++) {
					if (array[i][j] == 255 && !color_continue) {
						curr_row_node->next = new LLNode(j);
						curr_row_node = curr_row_node->next;
						if (j + 1 < col && array[i][j + 1] != 255) {
							curr_row_node->next = new LLNode(j);
							curr_row_node = curr_row_node->next;
						}
						else {
							color_continue = true;
						}
					}
					if ((array[i][j] != 255 && color_continue)) {
						curr_row_node->next = new LLNode(j - 1);
						curr_row_node = curr_row_node->next;
						color_continue = false;
					}
					if ((j == col - 1 && color_continue)) {
						curr_row_node->next = new LLNode(j);
						curr_row_node = curr_row_node->next;
						color_continue = false;
					}
				}
				color_continue = false;
				curr_row_node->next = new LLNode(-2);
				curr_row_node = curr_row_node->next;
				// for traversal of black color
				for (int j = 0; j < col; j++) {
					if (array[i][j] == 0 && !color_continue) {
						curr_row_node->next = new LLNode(j);
						curr_row_node = curr_row_node->next;
						if (j + 1 < col && array[i][j + 1] != 0) {
							curr_row_node->next = new LLNode(j);
							curr_row_node = curr_row_node->next;
						}
						else {
							color_continue = true;
						}
					}
					if ((array[i][j] != 0 && color_continue)) {
						curr_row_node->next = new LLNode(j - 1);
						curr_row_node = curr_row_node->next;
						color_continue = false;
					}
					if ((j == col - 1 && color_continue)) {
						curr_row_node->next = new LLNode(j);
						curr_row_node = curr_row_node->next;
						color_continue = false;
					}
				}
				curr_row_node->next = new LLNode(-1);
				curr_row_node = curr_row_node->next;
				color_continue = false;
			}
		}
		else {
			cout << "Image is Already Loaded...\n";
		}
	}

	void print() {
		LLNode* curr_row_head = head;
		LLNode* curr_row_node = head;

		while (true) {
			curr_row_node = curr_row_head;
			while (curr_row_node) {
				cout << curr_row_node->value << "\t";
				if (curr_row_node->next == NULL) { break; }
				else {
					curr_row_node = curr_row_node->next;
				}
			}
			if (curr_row_head->down == NULL) { break; }
			else {
				curr_row_head = curr_row_head->down;
			}
			cout << endl;
		}
	}
};

class QTNode {
public:
	QTNode* nw;
	QTNode* ne;
	QTNode* sw;
	QTNode* se;
	string color;

	QTNode() {
		nw = NULL;
		ne = NULL;
		sw = NULL;
		se = NULL;
		color = "white";
	}
	QTNode(string color) {
		nw = NULL;
		ne = NULL;
		sw = NULL;
		se = NULL;
		this->color = color;
	}
};

class QuadTree {
	QTNode* head;
	int height;
	int width;
public:
	QuadTree() {
		head = NULL;
	}

	TwoDLL* divideLinkedList(TwoDLL& image, int rowMin, int rowMax, int colMin, int colMax) {
		LLNode* NewList = new LLNode;
		LLNode* imageList = image.head;
		for (int i = 0; i < rowMin; i++) {
			imageList = imageList->down;
		}
		LLNode* ImageTemp = imageList;  // moving horizontally
		LLNode* NewListRow = NewList;
		LLNode* newListTemp = NewListRow;		// moving horizontally
		bool valueStarted = false;
		bool turn = false;
		for (int i = rowMin; i <= rowMax; i++) {
			if (i == rowMin) {
				NewListRow = NewList;
				newListTemp = NewListRow;
			}
			else {
				NewListRow->down = new LLNode;
				NewListRow = NewListRow->down;
				newListTemp = NewListRow;
				imageList = imageList->down;
				ImageTemp = imageList;
			}
			if (ImageTemp) {
				newListTemp->value = ImageTemp->value;
				ImageTemp = ImageTemp->next;
			}
			while (ImageTemp) {
				/*if (!turn && ImageTemp->value < colMin && !(ImageTemp->value == -2 || ImageTemp->value == -1)) {
					valueStarted = false;
				}
				else*/ if (!turn && !valueStarted && ImageTemp->value < colMin && ImageTemp->next && ImageTemp->next->value >= colMin && !(ImageTemp->value == -2 || ImageTemp->value == -1)) {
					newListTemp->next = new LLNode;
					newListTemp = newListTemp->next;
					newListTemp->value = colMin;
					if (!(ImageTemp->value == -2 || ImageTemp->value == -1)) {
						valueStarted ? valueStarted = false : valueStarted = true;
					}
				}
				else if ((ImageTemp->value >= colMin && ImageTemp->value <= colMax) || (ImageTemp->value == -2 || ImageTemp->value == -1)) {
					/*if (turn == false && !valueStarted && !(ImageTemp->value == -2 || ImageTemp->value == -1)) {
						newListTemp->next = new LLNode;
						newListTemp = newListTemp->next;
						newListTemp->value = colMin;
						valueStarted ? valueStarted = false : valueStarted = true;
					}*/
					newListTemp->next = new LLNode;
					newListTemp = newListTemp->next;
					newListTemp->value = ImageTemp->value;
					if (!(ImageTemp->value == -2 || ImageTemp->value == -1)) {
						valueStarted ? valueStarted = false : valueStarted = true;
					}
				}
				else if (valueStarted) {
					newListTemp->next = new LLNode;
					newListTemp = newListTemp->next;
					newListTemp->value = colMax;
					valueStarted = false;
				}
				if (!(ImageTemp->value == -2 || ImageTemp->value == -1))
					turn ? turn = false : turn = true;

				if (ImageTemp->next == NULL) { break; }
				ImageTemp = ImageTemp->next;
			}
			valueStarted = false;
			turn = false;
		}
		TwoDLL* quadrant = new TwoDLL(NewList);
		return quadrant;
	}

	/*TwoDLL* divideLinkedList(TwoDLL& image, int quadrant) {
		int rowMin = 0;
		int rowMax = 0;
		int colMin = 0;
		int colMax = 0;
		if (quadrant == 1) {
			rowMax = (height - 1) / 2;
			colMax = (width - 1) / 2;
		}
		else if (quadrant == 3) {
			colMax = (width - 1) / 2;
			rowMin = ((height - 1) / 2) + 1;
			rowMax = height - 1;
		}
		if (quadrant == 2) {
			rowMax = (height - 1) / 2;
			colMin = ((width - 1) / 2) + 1;
			colMax = width - 1;
		}
		if (quadrant == 4) {
			rowMin = ((height - 1) / 2) + 1;
			rowMax = height - 1;
			colMin = ((width - 1) / 2) + 1;
			colMax = width - 1;
		}
		TwoDLL* ptr = divideLinkedList(image, rowMin, rowMax, colMin, colMax);
		ptr->print();
		return ptr;
	}*/

	string getColor(TwoDLL* image, int rowMin, int rowMax) {
		return "Error";
	}

	string getColor(TwoDLL image, int quadrant, int height, int width, int heightStart, int widthStart) {
		int rowMin = 0;
		int rowMax = 0;
		int colMin = 0;
		int colMax = 0;
		/*if (quadrant == 1) {
			rowMin = heightStart;
			rowMax = heightStart + (height - 1) / 2;
			colMin = widthStart;
			colMax = widthStart + (width - 1) / 2;
		}
		if (quadrant == 2) {
			rowMin = heightStart;
			rowMax = heightStart + (height - 1) / 2;
			colMin = widthStart + (width - 1) / 2 + 1;
			colMax = widthStart + width - 1;
		}
		if (quadrant == 3) {
			colMin = widthStart;
			colMax = widthStart + (width - 1) / 2;
			rowMin = heightStart + ((height - 1) / 2) + 1;
			rowMax = heightStart + height - 1;
		}
		if (quadrant == 4) {
			rowMin = heightStart + ((height - 1) / 2) + 1;
			rowMax = heightStart + height - 1;
			colMin = widthStart + (width - 1) / 2 + 1;
			colMax = widthStart + width - 1;
		}*/
		if (quadrant == 1) {
			rowMax = (height - 1) / 2;
			colMax = (width - 1) / 2;
		}
		if (quadrant == 2) {
			rowMax = (height - 1) / 2;
			colMin = (width - 1) / 2 + 1;
			colMax = width - 1;
		}
		if (quadrant == 3) {
			colMax = (width - 1) / 2;
			rowMin = ((height - 1) / 2) + 1;
			rowMax = height - 1;
		}
		if (quadrant == 4) {
			rowMin = ((height - 1) / 2) + 1;
			rowMax = height - 1;
			colMin = (width - 1) / 2 + 1;
			colMax = width - 1;
		}
		TwoDLL* quadLL = divideLinkedList(image, rowMin, rowMax, colMin, colMax);
		cout << "\n\nQuadrant - " << quadrant << endl;
		quadLL->print();
		bool istrue = true;
		LLNode* temp = quadLL->head;
		for (int i = rowMin; i <= rowMax && istrue; i++) {
			if (temp->next && temp->next->value != -2) { istrue = false; break; }
			if (temp->down == NULL) { break; }
			temp = temp->down;
		}
		if (istrue)
			return "black";
		else {
			temp = quadLL->head;
			bool istrue = true;
			LLNode* tempRow = temp;
			for (int i = colMin; i <= colMax && istrue; i++) {
				tempRow = temp;
				while (tempRow->value != -2) {
					tempRow = tempRow->next;
				}
				if (tempRow->next->value != -1) { istrue = false; break; }
				temp = temp->down;
			}
			if (istrue)
				return "white";
			else
				return "gray";
		}
	}

	void constructTree(TwoDLL& image, QTNode*& node, int height, int width, int heightStart, int widthStart) {
		cout << "Height: " << height << "\tWidth: " << width << endl;
		if (node->color == "gray") {
			////cout << "Entered" << endl;
			//node->ne = new QTNode;
			//node->nw = new QTNode;
			//node->se = new QTNode;
			//node->sw = new QTNode;
			////cout << "Nodes Created" << endl;
			//node->nw->color = getColor(image, 1, height, width, heightStart, widthStart);
			//if (node->nw->color == "gray") {
			//	constructTree(*divideLinkedList(image, heightStart , heightStart + (height-1) / 2, widthStart, widthStart + (width - 1) / 2), node->nw, height/2, width/2, heightStart, widthStart);
			//}
			////cout << "N-W: " << node->nw->color << endl;
			//node->ne->color = getColor(image, 2, height, width, heightStart, widthStart + width / 2);
			//if (node->ne->color == "gray") {
			//	constructTree(*divideLinkedList(image, heightStart, heightStart + (height - 1) / 2, widthStart + ((width - 1) / 2) + 1, widthStart + width - 1), node->ne, height / 2, width / 2, heightStart, widthStart + width/2);
			//}
			////cout << "N-E: " << node->ne->color << endl;
			//node->sw->color = getColor(image, 3, height, width, heightStart + height / 2, widthStart);
			//if (node->sw->color == "gray") {
			//	constructTree(*divideLinkedList(image, heightStart + ((height - 1) / 2) + 1, heightStart + height - 1, widthStart, widthStart + (width - 1) / 2), node->sw, height / 2, width / 2, heightStart+height/2, widthStart);
			//}
			////cout << "S-W: " << node->sw->color << endl;
			//node->se->color = getColor(image, 4, height, width, heightStart + height / 2, widthStart + width / 2);
			//if (node->se->color == "gray") {
			//	constructTree(*divideLinkedList(image, heightStart + ((height - 1) / 2) + 1, heightStart + height -1, widthStart + ((width - 1) / 2) + 1, widthStart + width-1), node->se, height / 2, width / 2, heightStart+height/2, widthStart+width/2);
			//}
			////cout << "S-E: " << node->se->color << endl;


			node->ne = new QTNode;
			node->nw = new QTNode;
			node->se = new QTNode;
			node->sw = new QTNode;
			//cout << "Nodes Created" << endl;
			node->nw->color = getColor(image, 1, height, width, heightStart, widthStart);
			if (node->nw->color == "gray") {
				constructTree(*divideLinkedList(image, heightStart, heightStart + (height - 1) / 2, widthStart, widthStart + (width - 1) / 2), node->nw, height / 2, width / 2, heightStart, widthStart);
			}
			//cout << "N-W: " << node->nw->color << endl;
			node->ne->color = getColor(image, 2, height, width, heightStart, widthStart + width / 2);
			if (node->ne->color == "gray") {
				constructTree(*divideLinkedList(image, heightStart, heightStart + (height - 1) / 2, widthStart + ((width - 1) / 2) + 1, widthStart + width - 1), node->ne, height / 2, width / 2, heightStart, widthStart + width / 2);
			}
			//cout << "N-E: " << node->ne->color << endl;
			node->sw->color = getColor(image, 3, height, width, heightStart + height / 2, widthStart);
			if (node->sw->color == "gray") {
				constructTree(*divideLinkedList(image, heightStart + ((height - 1) / 2) + 1, heightStart + height - 1, widthStart, widthStart + (width - 1) / 2), node->sw, height / 2, width / 2, heightStart + height / 2, widthStart);
			}
			//cout << "S-W: " << node->sw->color << endl;
			node->se->color = getColor(image, 4, height, width, heightStart + height / 2, widthStart + width / 2);
			if (node->se->color == "gray") {
				constructTree(*divideLinkedList(image, heightStart + ((height - 1) / 2) + 1, heightStart + height - 1, widthStart + ((width - 1) / 2) + 1, widthStart + width - 1), node->se, height / 2, width / 2, heightStart + height / 2, widthStart + width / 2);
			}


		}
		return;
	}

	void createTree(TwoDLL image, int height, int width) {
		this->height = height;
		this->width = width;
		head = new QTNode("gray");
		constructTree(image, head, height, width, 0, 0);
	}

	void printTree(QTNode* node, int depth = 0) {
		if (node == NULL) {
			return;
		}

		// Print the current node
		cout << string(depth, '-') << " " << node->color << endl;

		// Recursively print the children nodes
		printTree(node->nw, depth + 1);
		printTree(node->ne, depth + 1);
		printTree(node->sw, depth + 1);
		printTree(node->se, depth + 1);
	}

	void writeTreeToFile(QTNode* node, int depth, ofstream& outfile) {
		if (node == NULL) {
			return;
		}

		// Write the current node to file
		outfile << string(depth, '-') << " " << node->color << endl;

		// Recursively write the children nodes to file
		writeTreeToFile(node->nw, depth + 1, outfile);
		writeTreeToFile(node->ne, depth + 1, outfile);
		writeTreeToFile(node->sw, depth + 1, outfile);
		writeTreeToFile(node->se, depth + 1, outfile);
	}

	void writeToFile() {
		ofstream outfile("quadtree.txt");
		outfile << height << '-' << width << endl;
		writeTreeToFile(head, 0, outfile);
		outfile.close();
	}

	QTNode* readTreeFromFile(ifstream& infile) {

		string line;
		getline(infile, line);

		if (line.empty()) {
			return NULL;
		}

		int depth = 0;
		while (line[depth] == '-') {
			depth++;
		}

		string color = line.substr(depth + 1, line.length() - depth + 1);

		QTNode* node = new QTNode(color);
		if (color == "gray") {
			node->nw = readTreeFromFile(infile);
			node->ne = readTreeFromFile(infile);
			node->sw = readTreeFromFile(infile);
			node->se = readTreeFromFile(infile);
			return node;
		}
		return node;
	}


	void readFile() {
		ifstream infile("quadtree.txt");
		string temp;
		getline(infile, temp, '-');
		height = stoi(temp);
		getline(infile, temp);
		width = stoi(temp);
		head = readTreeFromFile(infile);
		print();
		infile.close();
	}

	void print() {
		cout << "Height: " << height << "\tWidth: " << width << endl;
		printTree(head, 0);
	}

	void convertData(QTNode* node, int**& img_data, int minX, int maxX, int minY, int maxY, int h, int w, int hs, int ws) {
		if (node) {
			if (node->color == "gray") {
				convertData(node->nw, img_data, hs, hs + (h - 1) / 2, ws, ws + (w - 1) / 2, h / 2, w / 2, hs, ws);
				convertData(node->sw, img_data, hs + (h - 1) / 2 + 1, hs + h - 1, ws, ws + (w - 1) / 2, h / 2, w / 2, hs + h / 2, ws);
				convertData(node->ne, img_data, hs, hs + (h - 1) / 2, ws + (w - 1) / 2 + 1, ws + w - 1, h / 2, w / 2, hs, ws + w / 2);
				convertData(node->se, img_data, hs + (h - 1) / 2 + 1, hs + h - 1, ws + (w - 1) / 2 + 1, ws + w - 1, h / 2, w / 2, hs + h / 2, ws + w / 2);
			}
			else {
				for (int i = minX; i <= maxX; i++) {
					for (int j = minY; j <= maxY; j++) {
						img_data[i][j] = (node->color == "black" ? 0 : 255);
					}
				}
			}
		}
	}

	int** treeToDMA() {
		int** img_data = new int* [height];
		for (int i = 0; i < height; i++)
		{
			img_data[i] = new int[width];
		}
		convertData(head, img_data, 0, height - 1, 0, width - 1, height, width, 0, 0);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << img_data[i][j] << "  ";
			}
			cout << endl;
		}
		return img_data;
	}
};


