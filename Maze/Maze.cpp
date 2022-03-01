#include <iostream>
#include <time.h>
#include <vector>
#include <array>

class Room
{
private:
	int x;
	int y;
	char value;
	bool isVisited;
	Room* previousRoom;
public:
	Room(int x, int y) {
		this->x = x;
		this->y = y;
		this->value = '#';
		this->isVisited = false;
		this->previousRoom = nullptr;
	}
	~Room() {
		
	}
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	char getValue() {
		return this->value;
	}
	void setValue(char value) {
		this->value = value;
	}
	bool getIsVisited() {
		return this->isVisited;
	}
	void setIsVisited(bool isVisited) {
		this->isVisited = isVisited;
	}
	Room* getPreviousRoom() {
		return this->previousRoom;
	}
	void setPreviousRoom(Room* room) {
		this->previousRoom = room;
	}
};
class Maze
{
private:
	unsigned int length;
	std::vector<std::vector<Room*>> maze;
	Room* currentRoom;
public:
	Maze(unsigned int length) {
		this->length = length;
		this->drawPath();
		this->drawMap();
	}
	~Maze() {
		for (auto &i : maze)
		{
			for (auto* j : i)
			{
				delete j;
			}
		}
	}
	void move(std::string direction) {
		if(direction == "Left"){
			this->currentRoom->setValue('<');
			this->currentRoom->setIsVisited(true);
			this->currentRoom = this->maze[this->currentRoom->getY()][this->currentRoom->getX() - 1];
			this->currentRoom->setPreviousRoom(maze[this->currentRoom->getY()][this->currentRoom->getX() + 1]);
			return;
		}
		if (direction == "Right") {
			this->currentRoom->setValue('>');
			this->currentRoom->setIsVisited(true);
			this->currentRoom = maze[this->currentRoom->getY()][this->currentRoom->getX() + 1];
			this->currentRoom->setPreviousRoom(maze[this->currentRoom->getY()][this->currentRoom->getX() - 1]);
			return;
		}
		if (direction == "Up") {
			this->currentRoom->setValue('^');
			this->currentRoom->setIsVisited(true);
			this->currentRoom = maze[this->currentRoom->getY() - 1][this->currentRoom->getX()];
			this->currentRoom->setPreviousRoom(maze[this->currentRoom->getY() + 1][this->currentRoom->getX()]);
			return;
		}
		if (direction == "Down") {
			this->currentRoom->setValue('|');
			this->currentRoom->setIsVisited(true);
			this->currentRoom = maze[this->currentRoom->getY() + 1][this->currentRoom->getX()];
			this->currentRoom->setPreviousRoom(maze[this->currentRoom->getY() - 1][this->currentRoom->getX()]);
			return;
		}
		if (direction == "Back") {
			this->currentRoom->setValue('*');
			this->currentRoom->setIsVisited(true);
			this->currentRoom = this->currentRoom->getPreviousRoom();
			return;
		}
	}
	void drawPath() {
		for (size_t i = 0; i < this->length; i++)
		{
			std::vector<Room*> row;
			for (size_t j = 0; j < this->length; j++) {
				row.push_back(new Room(j, i));
			}
			maze.push_back(row);
		}

		this->currentRoom = this->maze[0][0];

		for (size_t i = 0; i < this->length * this->length - 1;)
		{
			this->currentRoom->setValue('x');
			this->drawMap();
			std::cout << std::endl;
			std::vector<std::string> options = {"Left", "Right", "Up", "Down"};
			if (this->currentRoom->getX() == 0) {
				//left
				options.erase(options.begin());
			}
			else if (maze[this->currentRoom->getY()][this->currentRoom->getX() - 1]->getIsVisited()) {
				//left
				options.erase(options.begin());
			}
			if (this->currentRoom->getX() == this->length - 1) {
				//right
				options.erase(options.end() - 2);
			}
			else if (maze[this->currentRoom->getY()][this->currentRoom->getX() + 1]->getIsVisited()) {
				//right
				options.erase(options.end() - 2);
			}
			if (this->currentRoom->getY() == 0) {
				//up
				options.erase(options.end() - 1);
			}
			else if (maze[this->currentRoom->getY() - 1][this->currentRoom->getX()]->getIsVisited()) {
				//up
				options.erase(options.end() - 1);
			}
			if (this->currentRoom->getY() == this->length - 1) {
				//down
				options.erase(options.end());
			}
			else if (maze[this->currentRoom->getY() + 1][this->currentRoom->getX()]->getIsVisited()) {
				//down
				options.erase(options.end());
			}

			if (options.size() == 0) {
				move("Back");
			}
			else
			{
				move(options[rand() % options.size()]);
				++i;
			}
		}
		this->currentRoom = this->maze[0][0];
		std::cout << std::endl;
	}
	void drawMap() {
		for (size_t i = 0; i < this->length; i++)
		{
			for (size_t j = 0; j < this->length; j++) {
				std::cout << this->maze[i][j]->getValue() << " ";
			}
			std::cout << std::endl;
		}
	}

};

int main()
{
	srand(time(0));
	Maze maze = Maze(10);
}
