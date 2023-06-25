#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void admin();
void regis();
void login();
void menu_admin();
void sewa();

int a, i=0, selisih_user, selisih_adm, selisih;

FILE *stok;
FILE *tgl;
FILE *dat;

struct{
	int tanggal, bulan, tahun;
}upd;
struct{
	int mobil, motor;
}cek;
struct{
	char user[100],pass[100];
	int tanggal, bulan, tahun;
}user,current_user;

main(){
	system("cls");
	printf("\n\t================================\n\t Created by Adam Nuel Wafi Yogi \n\t================================\n");
	printf("\nMenu:\n1. Login sebagai admin\n2. Registrasi\n3. Login\n4. Exit\nPilihan : ");scanf("%d",&a); getchar();
	switch(a){
		case 1: admin(); break;
		case 2: regis(); break;
		case 3: login(); break;
		case 4: system("exit"); break;
		default: printf("\nPilihan tidak ada! Silahkan pilih lagi!!!\n"); system("pause"); main();
	}
}

void admin(){
	char username[20], pw[20];
	system("cls");
	printf("\n\t==============================\n\t\t Login Admin \n\t==============================\n");
	printf("\nUsername : ");gets(username);
	printf("Password : ");gets(pw);
	if(strcmp(username,"admin")==0 && strcmp(pw,"admin")==0){
		printf("\nLogin berhasil, Selamat datang admin!!\n\n"); system("pause"); menu_admin();
	}
	else{
		printf("\nLogin gagal!!!\n\n"); system("pause"); main();
	}
}

void menu_admin(){
	int i=1;
	system("cls");
	printf("\n\t==============================\n\t Selamat datang di menu admin \n\t==============================\n");
	printf("\nMenu:\n1. Update tanggal\n2. Cek dan ubah stok kendaraan\n3. Tampilkan list tersewa\n4. Kembali\nPilihan : ");scanf("%d",&a);getchar();
	switch(a){
		case 1:
			system("cls");
			printf("\n\t================\n\t Update Tanggal \n\t================\n\n");
			tgl = fopen("tgl.dat", "rb");
				while(fread(&upd,sizeof(upd),1,tgl)==1){
				printf("Tanggal saat ini : %d-%d-%d\n", upd.tanggal, upd.bulan, upd.tahun);
				}
			fclose(tgl);
			printf("==update==\n");
			tgl = fopen("tgl.dat","wb");
			printf("Tanggal : ");scanf("%d", &upd.tanggal);
			printf("Bulan   : ");scanf("%d", &upd.bulan);
			printf("Tahun   : ");scanf("%d", &upd.tahun);
			selisih_adm = abs((upd.tahun) * 365 + (upd.bulan) * 30 + (upd.tanggal));
			printf("\n== Tanggal Berhasil Diubah !!! ==\n");
			fwrite(&upd, sizeof(upd),1, tgl);
			fclose(tgl); system("pause"); menu_admin();
		case 2:
			system("cls");
			printf("\n\t=============================\n\t Cek dan ubah stok kendaraan \n\t=============================\n\n");
			stok = fopen("stok.dat", "rb");
				while(fread(&cek,sizeof(cek),1,stok)==1){
				printf("Jumlah stok saat ini : ");
				printf("\n1. Mobil : %d", cek.mobil);
				printf("\n2. Motor : %d", cek.motor);
				}
			fclose(stok);
			printf("\nPilih stok yang ingin diubah:\n1. Mobil\n2. Motor\n3. Kembali\nPilihan : ");scanf("%d",&a); getchar();
			switch(a){
			case 1:
				stok = fopen("stok.dat", "wb");
				printf("Ubah stok mobil menjadi : "); scanf("%d", &cek.mobil);
				printf("Stok mobil berhasil diubah!!\n");
				fwrite(&cek, sizeof(cek),1, stok);
				fclose(stok); system("pause"); menu_admin();
			case 2: 
				stok = fopen("stok.dat", "wb");
				printf("Ubah stok motor menjadi : "); scanf("%d", &cek.motor);
				printf("Stok motor berhasil diubah!!\n");
				fwrite(&cek, sizeof(cek),1, stok);
				fclose(stok); system("pause"); menu_admin();
			case 3: 
				menu_admin();
		default: printf("\nPilihan tidak ada! Silahkan pilih lagi!!!\n"); system("pause"); menu_admin();
	}
		case 3:
			system("cls");
			printf("\n\t========================\n\t Tampilkan List Tersewa \n\t========================\n\n");
			dat = fopen("datauser.dat","rb");
			tgl = fopen("tgl.dat","rb");
			fread(&user,sizeof(user),1,dat);
			fread(&user,sizeof(user),1,tgl);
			if ((dat = fopen("datauser.dat","rb")) != NULL) {
				while(fread(&user, sizeof(user), 1, dat)) {
					if (user.bulan != 0){
					printf("%d. Username '%s' menyewa sampai tanggal %d - %d - %d\n", i, user.user, user.tanggal, user.bulan, user.tahun);
					i++;
				}
				}
			}
			else {
				printf("Tidak ada yang menyewa\n");
			}
			system("pause"); menu_admin();
			fclose(dat);
			fclose(tgl);
		case 4:
			main();
		default: printf("\nPilihan tidak ada! Silahkan pilih lagi!!!\n"); system("pause"); menu_admin();
	}
}

void regis(){
	system("cls");
		printf("\n\t===========\n\t Akun User \n\t===========\n\n");
		printf("Silahkan registrasi terlebih dahulu\n\n");
		printf("Username : "); gets(user.user);
		printf("Password : "); gets(user.pass);
		dat = fopen("datauser.dat","ab");
		fwrite(&user,sizeof(user),1,dat);
		fclose(dat);
		printf("\nPendaftaran Berhasil!!!\n"); system("pause"); main();
}
void login(){
	system("cls");
	char username[100], password[100];
	int status=0;
		printf("\n\t============\n\t Login User \n\t============\n\n");
		printf("Username : "); gets(username);
		printf("Password : "); gets(password);
		dat = fopen("datauser.dat","rb");
		while(fread(&user,sizeof(user),1,dat)==1){
			if(strcmp(user.user,username)==0 && strcmp(user.pass,password)==0){ 
				current_user=user;
				status=1; //status
			}
		}
		fclose(dat);
		
		if(status == 1){
			printf("\nSelamat datang %s !!!\n", username); system("pause"); sewa();
			sewa();
		}
		else{
			printf("Login gagal silahkan coba lagi !!!\n"); system("pause"); main();

}
}

void sewa(){
	int b;
	int status = 0;
	system("cls");
	printf("\n\t==============================\n\t Selamat datang di menu user \n\t==============================\n");
	printf("\nMenu:\n1. Sewa kendaraan\n2. Cek status sewa\n3. Perpanjang durasi sewa\n4. Pengembalian kendaraan\n5. Kembali\nPilihan : ");scanf("%d",&a);getchar();
	switch(a){
		case 1:
			system("cls");
			printf("\n\t===========\n\t Menu Sewa \n\t===========\n");
			if ((tgl = fopen("tgl.dat", "rb")) == NULL ){
				printf("Tanggal belum diupdate admin\n"); fclose(tgl);
				system("pause"); sewa();
			}
			else{
				tgl = fopen("tgl.dat", "rb");
				while(fread(&upd,sizeof(upd),1,tgl)==1){
					printf("Jumlah stok pertanggal : %d-%d-%d\n", upd.tanggal, upd.bulan, upd.tahun);
				}
			}
			stok = fopen("stok.dat", "rb");
			while(fread(&cek,sizeof(cek),1,stok)==1){
				printf("\n1. Mobil : %d", cek.mobil);
				printf("\n2. Motor : %d", cek.motor);
			}
			fclose(tgl);
			fclose(stok);
			printf("\nPilih jenis kendaraan yang ingin anda sewa\n");
			printf("1. Mobil\n2. Motor\n3. Kembali\nPilihan : "); scanf("%d",&a);
			switch(a){
				case 1:
					while(cek.mobil!='\0'){
						printf("\nSampai tanggal berapa anda ingin menyewa mobil?\n");
						printf("Tanggal : "); scanf("%d", &current_user.tanggal);
						printf("Bulan : "); scanf("%d", &current_user.bulan);
						printf("Tahun : "); scanf("%d", &current_user.tahun);
						selisih_user = abs((current_user.tahun) * 365 + (current_user.bulan) * 30 + (current_user.tanggal-upd.tanggal));
						if(selisih_user < selisih_adm){
							printf("\nKendaraan berhasil dikembalikan !!!\n\n"); system("pause"); sewa();
						}
						else{
						printf("\nAnda berhasil menyewa mobil sampai tanggal %d - %d - %d !!!\n", current_user.tanggal, current_user.bulan, current_user.tahun); 
						status = 1; cek.mobil--;
						system("pause"); sewa();
					}
					}
					printf("Mobil tidak tersedia untuk saat ini!!\n"); system("pause"); sewa();
				case 2:
					while(cek.motor!='\0'){
						printf("\nSampai tanggal berapa anda ingin menyewa motor?\n");
						printf("Tanggal : "); scanf("%d", &current_user.tanggal);
						printf("Bulan : "); scanf("%d", &current_user.bulan);
						printf("Tahun : "); scanf("%d", &current_user.tahun);
						printf("\nAnda berhasil menyewa mobil sampai tanggal %d - %d - %d !!!\n", current_user.tanggal, current_user.bulan, current_user.tahun); 
						status = 1; cek.motor--;
						system("pause"); sewa();
					}
					printf("Motor tidak tersedia untuk saat ini!!\n"); system("pause"); sewa();
				case 3:
					sewa();
				default:
					printf("\nNomer tidak sesuai yang tersedia !!!!\n\n"); system("pause"); sewa();
			}
		case 2:
			system("cls");
			printf("\n\t=================\n\t Cek status sewa \n\t=================\n");
			dat = fopen("datauser.dat","rb");
			tgl = fopen("tgl.dat", "rb");
			if(current_user.tanggal != '\0'){
				while(fread(&upd, sizeof(upd), 1, tgl)) {
					printf("== Tanggal saat ini adalah %d - %d - %d ==\n", upd.tanggal, upd.bulan, upd.tahun);
				}
				selisih = abs((current_user.tahun-upd.tahun) * 365 + (current_user.bulan-upd.bulan) * 30 + (current_user.tanggal-upd.tanggal));
				printf("\nSisa durasi sewa mu %d hari lagi\n", selisih);
			}
			else{
				printf("\n== Anda belum menyewa kendaraan ==\n");
			}
			fclose(dat); fclose(tgl);
			system("pause"); sewa();
		case 3:
			system("cls");
			printf("\n\t========================\n\t Perpanjang durasi sewa \n\t========================\n");
			dat = fopen("datauser.dat","wb+");
			if(current_user.tanggal!='\0'){
			printf("\nBerapa lama anda ingin perpanjang kendaraan anda? (Dalam hari, max 30 hari)\n");
			printf("=> "); scanf("%d", &b); current_user.tanggal=b;
				printf("== Anda berhasil menambah durasi sebanyak %d hari ==\n", b);
				fwrite(&current_user,sizeof(current_user),1,dat);
			}
			else{
				printf("\nAnda belum menyewa kendaraan !!!!\n\n");
			}
			fclose(dat); system("pause"); sewa();
		case 4:
			system("cls");
			printf("\n\t=====================\n\t Pengembalian Manual \n\t=====================\n");
			FILE *dat2;
			dat = fopen("datauser.dat", "rb"); 
			dat2 = fopen("datauser2.dat", "wb"); 
			while (fread(&current_user,sizeof (current_user),1, dat)==1){ 
			fwrite(&current_user, sizeof(current_user), 1, dat2); 
			} 
			fclose(dat); 
			fclose(dat2); 
			remove("datauser.dat"); 
			rename("datauser2.dat","datauser.dat"); 
			printf("\nKendaraan berhasil dikembalikan !!!!\n\n"); system("pause"); sewa();
		case 5:
			main();
		}
}
