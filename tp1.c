#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

typedef struct data {
	char employeeID[6];
	char nama[31];
	char tempat_lahir[31];
	int hari;
	int bulan;
	int tahun;
	char jabatan[51];
	struct data* next;
}data;

typedef struct node_list{
	data* head;
	data* tail;
	data* current;
	data* index;
	data* temp;
}node_list;


void input_data(node_list* list, char* employeeID, char* nama, char* tempat_lahir, int bulan, int hari, int tahun, char* jabatan) {
    data* data_baru = (data*)malloc(sizeof(data));
    strcpy(data_baru->employeeID, employeeID);
    strcpy(data_baru->nama, nama);
    strcpy(data_baru->tempat_lahir, tempat_lahir);
    data_baru->hari = hari;
    data_baru->bulan = bulan;
    data_baru->tahun = tahun;
    strcpy(data_baru->jabatan, jabatan);
    data_baru->next = NULL;
	
    if (list->head == NULL) {
        list->head = data_baru;
        printf("Data karyawan berhasil ditambahkan!\n");
        return;
    }
	
    data* last = list->head;
    while (last->next != NULL) last = last->next;
	
    last->next = data_baru;
    printf("Data karyawan berhasil ditambahkan!\n");
}

void swap(struct data* temp1, struct data* temp2) {
    char temp_employeeID[6];
    char temp_nama[31];
    char temp_tempat_lahir[31];
	int temp_hari;
	int temp_bulan;
	int temp_tahun;
	char temp_jabatan[51];
	
    strcpy(temp_employeeID, temp1->employeeID);
    strcpy(temp1->employeeID, temp2->employeeID);
    strcpy(temp2->employeeID, temp_employeeID);
    
    strcpy(temp_nama, temp1->nama);
    strcpy(temp1->nama, temp2->nama);
    strcpy(temp2->nama, temp_nama);
    
    strcpy(temp_tempat_lahir, temp1->tempat_lahir);
    strcpy(temp1->tempat_lahir, temp2->tempat_lahir);
    strcpy(temp2->tempat_lahir, temp_tempat_lahir);

    temp_hari = temp1->hari;
    temp1->hari = temp2->hari;
    temp2->hari = temp_hari;
    
    temp_bulan = temp1->bulan;
    temp1->bulan = temp2->bulan;
    temp2->bulan = temp_bulan;
    
    temp_tahun = temp1->tahun;
    temp1->tahun = temp2->tahun;
    temp2->tahun = temp_tahun;
    
    strcpy(temp_jabatan, temp1->jabatan);
    strcpy(temp1->jabatan, temp2->jabatan);
    strcpy(temp2->jabatan, temp_jabatan);
}

void bubbleSort(node_list* list) {
    int pindah;
    list->index = NULL;
	
    if (list->head == NULL)
        return;

    do {
        pindah = 0;
        list->current = list->head;

        while (list->current->next != list->index) {
            if (strcmp(list->current->employeeID, list->current->next->employeeID) > 0) {
                swap(list->current, list->current->next);
                pindah = 1;
            }
            else if ((strcmp(list->current->employeeID, list->current->next->employeeID) == 0) && (strcmp(list->current->nama, list->current->next->nama) > 0)) {
                swap(list->current, list->current->next);
                pindah = 1;
            }
            list->current = list->current->next;
        }
        list->index = list->current;
    } while (pindah);
}

void display_data(node_list* list) {
    data* data = list->head;
    if (data == NULL) {
        printf("Data kosong \n");
    } 
	else {
        printf("Berikut data yang ada pada sistem: \n\n");
        while (data != NULL) {
            printf("EmployeeID: %s\nNama: %s\nTempat,Tanggal Lahir: %s,%d/%d/%d\nJabatan: %s\n\n", 
			data->employeeID, data->nama, data->tempat_lahir, data->bulan, data->hari, data->tahun, data->jabatan);
            data = data->next;
        }
    }
}

void delete_data(node_list* list, char* employeeID) {
    data* data = list->head;
    list->temp = data->next;
    int flag = 0;
    
    if (strcmp(data->employeeID, employeeID) == 0) {
        list->head = list->temp;
        free(data);
        printf("Data berhasil dihapus \n");
        flag = 1;
    }
    
    while (list->temp != NULL) {
        if (strcmp(list->temp->employeeID, employeeID) == 0) {
			data->next = list->temp->next;
            free(list->temp);
            printf("Data berhasil dihapus \n");
            flag = 1;
            break;
        }
        data = list->temp;
        list->temp = list->temp->next;
    }
   
    if (flag==0) printf("Data tidak ada di sistem \n");
	getchar();
}

void delete_all(node_list* list)
{
    while(list->head != NULL)
    {
        list->temp = list->head;
        list->head = list->head->next;
        free(list->temp);
    }

    printf("Semua data telah terhapus \n");
}

bool validate_count_data(node_list* list) {
    int count = 0;
	list->temp = list->head;
    while (list->temp != NULL) {
        count++;
        if (count > 4 ){
            return false;
        }
        list->temp = list->temp->next;
    }
    return true;
}

//int getCount(node_list* list) {
//    int count = 0;
//    list->current = list->head;
//    while (list->current != NULL) {
//        count++;
//        list->current = list->current->next;
//    }
//    return count;
//}

int main() {
	
    node_list node_list;
    node_list.head = NULL;
    node_list.tail = NULL;
    int pilihan = 0;
    char employeeID[6];
    char nama[31];
    char tempat_lahir[31];
    int hari,bulan,tahun;
    char jabatan[51];
    bool is_valid;
    char c;


    while (pilihan != 5) {
    	printf("Sistem penambahan data karyawan PT XYZ\n");
        printf("1. Tambah Data Karyawan\n");
        printf("2. Hapus 1 Data Karyawan\n");
        printf("3. Hapus Semua Data Karyawan\n");
        printf("4. Tampilkan Data Karyawan\n");
        printf("5. Keluar\n");
        printf("Silakan pilih menu: "); scanf("%d", &pilihan); 
		getchar();

        switch (pilihan) {
            case 1:
            	is_valid = validate_count_data(&node_list);
			    if (!is_valid) {
			    	printf("Tidak bisa input data Karyawan. Sudah terdapat 5 data Karyawan pada sistem\n");
			    	printf("Apabila mau input data karyawan, hapus data karyawan terlebih dahulu\n");
			    	getchar();
					system("cls");
			    	break;
				}
				while(1) {
					int alpha = 0;
					int eid = 0;
					printf("Masukkan id karyawan (5 angka): "); scanf("%5s", employeeID);
   					while ((c = getchar()) != '\n' && c != EOF) {}
   					if (strlen(employeeID) != 5) eid = 1;
                	for(int i = 0; employeeID[i] != '\0'; i++) {
				      if(isalpha(employeeID[i])) alpha = 1;
					}
					if((alpha)==0 && (eid == 0)) break;
					else if(eid==1) printf("Id karyawan tidak terdiri dari 5 angka\n");
					else printf("Terdapat huruf pada id karyawan\n");
				}
                printf("Masukkan nama: "); scanf(" %30[^\n]", nama); getchar();
                printf("Masukkan tempat lahir: "); scanf(" %30[^\n]", tempat_lahir); getchar();
                while(true) {
                	printf("Masukkan tanggal lahir dalam angka (bulan/tanggal/tahun): "); scanf("%d/%d/%d", &bulan,&hari,&tahun);
                	if (bulan>12) printf("Bulan tidak sesuai");
                	else if ((bulan==1||bulan==3||bulan==5||bulan==7||bulan==8||bulan==10||bulan==12)&&(hari>31)) printf("Tanggal tidak sesuai\n");
    	            else if ((bulan==4||bulan==6||bulan==9||bulan==11)&&(hari>30)) printf("Tanggal tidak sesuai\n");
    	            else if ((bulan==2) && (hari>28)) printf("Tanggal tidak sesuai\n");
					else break;
				}
                printf("Masukkan jabatan karyawan: "); scanf(" %50[^\n]", jabatan); getchar();
                input_data(&node_list, employeeID, nama, tempat_lahir, bulan, hari ,tahun,jabatan);
                getchar();
				system("cls");
                break;
            case 2:
                printf("Masukkan id karyawan (5 angka): "); scanf("%5s", employeeID);
                while ((c = getchar()) != '\n' && c != EOF) {}
                delete_data(&node_list, employeeID);
				system("cls");
                break;
            case 3:
				delete_all(&node_list);
				getchar();
				system("cls");
                break;
            case 4:
                bubbleSort(&node_list);
				display_data(&node_list);
				getchar();
				system("cls");
                break;
            case 5:
                printf("Terima kasih sudah menggunakan program ini!\n");
                break;
            default:
                printf("Pilihan tidak valid, silakan coba lagi!\n");
                getchar();
				system("cls");
        }
    }
    return 0;
}
