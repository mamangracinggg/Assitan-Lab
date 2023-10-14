#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define TABLE_SIZE 25


int main();

#define SIZE 4
int grid[SIZE][SIZE];
int score = 0;
void inisiasiGridSize(){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			grid[i][j] = 0;
		}
	}
}

void printGrid(){
	system("cls");
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(grid[i][j] == 0){
				printf("    -");
			}else{
				printf("%5d", grid[i][j]);
			}
		}
		printf("\n");
	}
	puts("");
	printf("Score: %d\n", score);
}

int isGridEmpty(int x, int y){
	return grid[x][y] == 0; //jika true maka tiles itu kosong dan sebaliknya
}

int isFullGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {//jika ada satu saja maka tidak semua tiles terisi
                return 0; 
            }
        }
    }
    return 1;
}

int generateRandomTileValue() {
	int possibility;
	if(score < 1000){
		possibility = 70;
	}else{
		possibility = 30;
	}

    return (rand() % 100 < possibility) ? 2 : 4;
}

void spawnRandomTile() {
    if (!isFullGrid()) { //jika semua grid belum terisi spawn tile in random 
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (!isGridEmpty(x, y)); //jika grid sudah ada value cari terus sampai didapat (x,y) di tempat kosong

        grid[x][y] = generateRandomTileValue();
    }
}

void mergeTiles(int x, int y, int newX, int newY) {
    grid[newX][newY] *= 2; //karena tiles nilainya kelipatan 2 dan akan merge apabila nilai sama maka tinggal dikali 2
    grid[x][y] = 0;
    score += grid[newX][newY];
}

void swipeLeft() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (grid[i][j] != 0) {
                int x = i;
                int y = j;
                while (y > 0 && grid[x][y - 1] == 0) {
                    y--;
                }
                if (y > 0 && grid[x][y - 1] == grid[x][y]) {
                    mergeTiles(x, y, x, y - 1);
                } else if (y < j) {
                    grid[x][y] = grid[i][j];
                    grid[i][j] = 0;
                }
            }
        }
    }
}

void swipeRight(){
	int moved = 0;
	for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE - 2; j >= 0; j--) {
                for (int k = j; k < SIZE - 1; k++) {
                    if (grid[i][k] != 0) {
                        if (grid[i][k + 1] == 0) {
                            grid[i][k + 1] = grid[i][k];
                            grid[i][k] = 0;
                            moved = 1;
                        } else if (grid[i][k + 1] == grid[i][k]) {
                            grid[i][k + 1] *= 2;
                            grid[i][k] = 0;
                            score += grid[i][k + 1];
                            moved = 1;
                        }
                    }
                }
            }
        }
}

void swipeDown(){
	int moved = 0;
	for (int j = 0; j < SIZE; j++) {
            for (int i = SIZE - 2; i >= 0; i--) {
                for (int k = i; k < SIZE - 1; k++) {
                    if (grid[k][j] != 0) {
                        if (grid[k + 1][j] == 0) {
                            grid[k + 1][j] = grid[k][j];
                            grid[k][j] = 0;
                            moved = 1;
                        } else if (grid[k + 1][j] == grid[k][j]) {
                            grid[k + 1][j] *= 2;
                            grid[k][j] = 0;
                            score += grid[k + 1][j];
                            moved = 1;
                        }
                    }
                }
            }
        }
}

void swipeUp(){
	int moved = 0;
	for (int j = 0; j < SIZE; j++) {
            for (int i = 1; i < SIZE; i++) {
                for (int k = i; k > 0; k--) {
                    if (grid[k][j] != 0) {
                        if (grid[k - 1][j] == 0) {
                            grid[k - 1][j] = grid[k][j];
                            grid[k][j] = 0;
                            moved = 1;
                        } else if (grid[k - 1][j] == grid[k][j]) {
                            grid[k - 1][j] *= 2;
                            grid[k][j] = 0;
                            score += grid[k - 1][j];
                            moved = 1;
                        }
                    }
                }
            }
	}
}

int isGameOver() {
    // Check if there are no empty cells
    if (isFullGrid()) {
        // Check if no adjacent cells have the same value
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE - 1; j++) {
                if (grid[i][j] == grid[i][j + 1]) {
                    return 0;
                }
                if (grid[j][i] == grid[j + 1][i]) {
                    return 0;
                }
            }
        }
        return 1; // Game over
    }
    return 0; // Game continues
}

void addFile(char id[], char playerName[], int score){
	FILE *fp = fopen("highscore.txt", "a");
	fprintf(fp, "%s#%s#%d\n", id, playerName, score);
	fclose(fp);
}

struct Data{
	char id[100];
	char nama[100];
	int score;
};

struct Data temp[100];

void mergeSort(int l, int r, struct Data player[]) {
    if (l >= r) return;

    int m = (l + r) / 2;

    mergeSort(l, m, player);
    mergeSort(m + 1, r, player);

    int pl = l, pr = m + 1, pt = l;
    while (pl <= m && pr <= r) {
        if (player[pl].score > player[pr].score) {
            temp[pt] = player[pl];
            pl++;
        } else {
            temp[pt] = player[pr];
            pr++;
        }
        pt++;
    }
    
    while (pl <= m) {
        temp[pt] = player[pl];
        pl++;
        pt++;
    }
    while (pr <= r) {
        temp[pt] = player[pr];
        pr++;
        pt++;
    }

    for (int i = l; i <= r; i++) {
        player[i] = temp[i];
    }
}

void readFile() {
    FILE *fp = fopen("highscore.txt", "r");
    if (fp == NULL) {
        printf("No data to be read\n");
        return;
    }
    
    Data player[101];
    int counter = 0;
    
    while (fscanf(fp, "%[^#]#%[^#]#%d\n", player[counter].id, player[counter].nama, &player[counter].score) == 3) {
        counter++;
    }
    
    mergeSort(0, counter-1, player);
    
    printf("        No.  |ID        |Username        |Score\n");
    for (int i = 0; i < 10; i++) {
        printf("        %-3d  |%s \t|%-15s |%d\n", i+1, player[i].id, player[i].nama, player[i].score);
    }
     fclose(fp);
    printf("        Press ENTER to continue...");
    char temp = _getch();
	main();
}



void gamePage4(){
	srand(time(NULL));
    inisiasiGridSize();
    spawnRandomTile();
    spawnRandomTile();

    char move;

    while (1) {
        printGrid();

        if (isFullGrid() && !isGameOver()) {
            printf("Game Over!\n");
            break;
        }

        move = _getch();

        switch (move) {
            case 'w':
            case 'W':
                swipeUp();
                break;
            case 'a':
            case 'A':
                swipeLeft();
                break;
            case 's':
            case 'S':
                swipeDown();
                break;
            case 'd':
            case 'D':
                swipeRight();
                break;
            case 13: // Enter = 13 (ASCII)
            	printf("Press Enter To Continue...");
            	char temp = _getch();
            	system("cls");
                char playerName[20];
                bool valid;
                puts("Save Data...");
                do{
                	printf("Input Name [name length must be between 3-15]:");
	                scanf("%s", playerName); getchar();
	                puts(" ");
	                
	                int len = strlen(playerName);
	                if (len >= 3 && len <= 15) {
	                	char id[6];
	                	if(playerName[0] >= 'a' && playerName[0] <= 'z'){
	                		playerName[0] -= 32;
						}
						if(playerName[1] >= 'a' && playerName[1] <= 'z'){
	                		playerName[1] -= 32;
						}
						id[0] = playerName[0];
						id[1] = playerName[1];
						srand(time(NULL));
						int i = 2;
						do{
							int randomNumber = rand() % 10;
							id[i] = '0'+ randomNumber;
							i++;
						}while(i <= 4);
						
	                    addFile(id, playerName, score);
	                    main();
	                    
	                } else {
	                    valid == false;
	                }
				}while(valid == false);
                
                break;
        }

        if (isFullGrid() && isGameOver()) {
            printf("Game Over!\n");
            break;
        }

        spawnRandomTile();
    }
}

void logo(){
	puts("                                .:^:.. ..^^:..");
	puts("                          ...   ...:.     .......    .");
	puts("                            .   . ^.   :..:~77~~::..::.. ..");
	puts("                          ::::....:..:~7.: :^ ^:..:....:^^:^^");
	puts("                        ..      .. .^!777^~!?^~7:^::.  .5BGB##&#7.");
	puts("                             .:!!. .:^.77?P57P7!^::~::?5B&&#GGG5.");
	puts("                          .:^~^^: YJJGBGP5YY7J7!^^^?7YG##P7^7#&B:");
	puts("                        .^~:  ~J55PJ:.       ..~JPBBBY^. .:.JG!:!!^..");
	puts("                     ..^7~  .::???.         .~!JG&&#J:       .7!:.^77?!^..");
	puts("                   .:~7!:. ^Y^.  ..      .!JPB&&#Y:          .  :7!: ~G5?!:.");
	puts("                 .:7?7..!!       .:..^?YP&&&G7         .        ~J: .BP7J!:.");
	puts("               .:^777~^::7^          :JB&&#BG^ .                   .J! !YYYJ?^.");
	puts("              .:!JJJJ: :7G.         ?#&&&&B~                         ?5..^!~~!!:.");
	puts("             .:!YYY5~ .J&Y      . .5BBBBBG^                           YP  :?J!~!^.");
	puts("             .:!J?YJ^..P&!        P&&&&&#!             ..              #7 .^55?^~:");
	puts("              .^7!??^..P#? .  .   #&&&&&J:..   ...  .   ..  ...     . 5#..:J57!:.");
	puts("              .:!J~^.?G#5      .:.^JGBBBP5Y!^75GBGP5PJYPGPP5YYJ?!^    !&:.:???~:.");
	puts("               .^?5^:.JPBP!       .:::.. .!YYY&&&###&&&&YG##&&&&#B5:   !&:.^!5J.");
	puts("                .^??:.^^?77..                 ^:.  ..P&G:^&&&&&&&&7    PG ~7:JP7:.");
	puts("                .:^7? .~~J?7!                 .      7#^ P&&&&&&G^    :&^ 7?5?!:.");
	puts("                  .^J5.:!JPBBY            .:.       ^5^ 7###&#P^      G7..7G5!:.");
	puts("                   .^?5~^:~PBP.?!: ^^7^!^     .7: #&&#5        ~:.:PY:.");
	puts("                    .^!5J7..!B&PJY?J^J?YGY?7!:..^^:?#@&G7.        ..::^Y!^.");
	puts("                     .:^??J!77JY57 .: :?#BYGG!7~:7G&#5~.           .~^!J5!:.");
	puts("                       .:?JY..... :.^!J^^!7~7PGPJ~.          ... ^?Y57:.");
	puts("                          :75P:.  ^^!!^~!JYJ57:..^^....:^!:  ...5GP7^.");
	puts("                          ::.:^7.JY^?77Y5Y7^..::??5J???5J: :?Y!J5!:.");
	puts("                           .  .^.7G&###B5!^:.:.::......~?J?YB#BY7^:.");
	puts("                              .^^YJ5###BG5J7!7JYPPGYJ??YPPPY?7~:.");
	puts("                              ..:^^^........^!!!!!^^::...");
	puts("");
	puts("");
	puts("                        o---------------------------------------------o");
	puts("                        |      Breaking and Overcoming Challenges     |");
	puts("                        |    Through Courage Hardwork and Persistence |");
	puts("                        |           ~ Bluejackets 23-1 ~              |");
	puts("                        o---------------------------------------------o");
	puts("");
	puts("");
	puts("");
}	

void mainMenu(){
	puts("          ______             __            __    __");
	puts("         /      \           /  |          /  |  /  |");
	puts("        /$$$$$$  |  ______  $$ | __    __ $$ |  $$ |");
	puts("        $$ |  $$/  /      \ $$ |/  |  /  |$$  \/$$/");
	puts("        $$ |       $$$$$$  |$$ |$$ |  $$ | $$  $$<");
	puts("        $$ |   __  /    $$ |$$ |$$ |  $$ |  $$$$  \\");
	puts("        $$ \__/  |/$$$$$$$ |$$ |$$ \__$$ | $$ /$$  |");
	puts("        $$    $$/ $$    $$ |$$ |$$    $$ |$$ |  $$ |");
	puts("         $$$$$$/   $$$$$$$/ $$/  $$$$$$$ |$$/   $$/");
	puts("                                /  \__$$ |");
	puts("                                $$    $$/");
	puts("                                 $$$$$$/");
	puts("                                          ");
	printf("1. New Game\n");
	printf("2. Highscore\n");
	printf("3. Exit\n");
	printf(">>");
}

bool checkGrid(char n){
	char val[] = {'4', '6'};
	for(int i = 0; i < sizeof(val)/sizeof(val[0]); i++){
		if(n == val[i])return true;
	}
	return false;
}

bool check(char n){
	char val[] = {'1', '2', '3'};
	for(int i = 0; i < sizeof(val)/sizeof(val[0]); i++){
		if(n == val[i])return true;
	}
	return false;
}

int main(){
	char input;
	do{
		system("cls");
		mainMenu();
		scanf("%c", &input);
		getchar();
	}while(check(input) == false);
		if(input == '1'){
			char size;
			do{
				printf("Input Grid Size [4 or 6]:");
				scanf("%c", &size);
				getchar();
			}while(checkGrid(size) == false);
				if(size == '4'){
					gamePage4();
				}
				if(size == '6'){
	//				gamePage6();
				}
		}else if(input == '2'){
			system("cls");
			readFile();
		}else if(input == '3'){
			system("cls");
			logo();
		}
	return 0;
}
