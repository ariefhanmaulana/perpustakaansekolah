#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int max_size = 100;

// deklarasi variabel
int pilihan,pil;
string cariBuku;

struct databuku{
	int idbuku,jumlahbuku, thterbit;
	string judulbuku, namapengarang,tglMpinjam,tglAkhpinjam;
	bool pinjam;
};

struct queuepinjam {
    int nomor[max_size];
    string namaanggota[max_size];
    databuku* bkPinjam[max_size];
    int ekor;
};

struct queuepengembalian {
    int nomorpgl[max_size];
    string namaanggotapgl[max_size];
    int ekorpengembalian;
};

bool full(const queuepinjam& q) {
    return q.ekor == max_size - 1;
}

bool fullpengembalian(const queuepengembalian& qp) {
    return qp.ekorpengembalian == max_size - 1;
}

bool empty(const queuepinjam& q) {
    return q.ekor == -1;
}

bool emptypengembalian(const queuepengembalian& qp) {
    return qp.ekorpengembalian == -1;
}

struct bukukembali{
	int top;
	char data[10][10];
}tumpuk;


void inputbuku(databuku& b1);
void simpan(databuku b1[] , int& temp);
void sortdatabuku(databuku b1[], int temp);
void MasukAntrian(queuepinjam& q);
void KeluarAntrian(queuepinjam& q);
void caridanTampilBuku(const databuku b1[], int temp, const string& cariBuku);
void peminjamanbuku(queuepinjam& q, databuku b1[], int temp );
void MasukAntrianPengembalian(queuepengembalian& qp);
void KeluarAntrianPengembalian(queuepengembalian& qp);


int main() {
    databuku b1[max_size];
    int temp = 0;
    queuepinjam q; q.ekor = -1;
	queuepengembalian qp; qp.ekorpengembalian = -1;

    menu:
    system("cls");
	cout <<"============================================="<<endl;
	cout <<"| NO |      MENU                            |"<<endl;
	cout <<"============================================="<<endl;
    cout <<" 1.	 Input Data Buku "<< endl;	
    cout <<" 2.	 Daftar Buku Tersedia " << endl; 
    cout <<" 3.	 Pencarian Buku	" << endl;
    cout <<" 4.	 Mengambil Nomor Antrian " << endl;
    cout <<" 5.	 Peminjaman	" << endl;
    cout <<" 6.	 Pengembalian " << endl;
    cout <<" 0.	 Keluar " << endl;
	cout<<"=============================================="<<endl;
    cout << "Masukkkan Menu : " ; cin >> pilihan;

    if (pilihan == 1 ) {
		simpan(b1, temp);
		cout << endl << endl;
		a:
		cout << "-------------------" << endl;
		cout << "1. Input Data Kembali " << endl;
		cout << "2. Kembali ke menu utama " << endl;
		cout << "Input : " ; cin >>pil;
		if (pil == 1) {
			simpan(b1, temp);
			goto a;
		} else if (pil == 2){
			goto menu;
		}

	} else if (pilihan == 2) {
        sortdatabuku(b1, temp);
		cout << "-------------------" << endl;
		cout << "1. Kembali ke menu utama " << endl;
		int pil2;
		cout << "Input : " ; cin >>pil2;
		if (pil2 == 1) {
			goto menu;
		} 
	} else if (pilihan == 3) {
        cout << "\nMasukkan judul buku yang ingin dicari: ";
		cin.ignore();
    	cin>>cariBuku;
    
        caridanTampilBuku(b1, temp, cariBuku);
		
		cout << "-------------------" << endl;
		cout << "1. Kembali ke menu utama " << endl;
		int pil3;
		cout << "Input : " ; cin >>pil3;
		if (pil3 == 1) {
			goto menu;
		} 

	} else if (pilihan == 4) {
		system("cls");
		cout << "1. Mengambil Nomor Antrian Peminjaman " << endl;
		cout << "2. Mengambil Nomor Antrian Pengembalian " << endl;
		cout << "Pilihan ( 1/2 ) : " ; cin >> pil;
		if (pil == 1) {
			MasukAntrian(q);
			z:
        	cin >> pil;
            if (pil == 1) {
                system("cls");
                MasukAntrian(q);    
				goto z;
            } else if (pil == 2){
                goto menu;
			} else {
				cout << "Menu yang anda pilih tidak tersedia ";
            }
		} else if (pil == 2) {
			MasukAntrianPengembalian(qp);
			kembali:
        	cin >> pil;
            if (pil == 1) {
                system("cls");
                MasukAntrianPengembalian(qp);    
				goto kembali;
            } else if (pil == 2){
                goto menu;
			} else {
				cout << "Menu yang anda pilih tidak tersedia ";
            }
		} else {
			cout << "Menu yang anda pilih tidak tersedia ";
		}
		
	} else if (pilihan == 5) {
		system("cls");
        peminjamanbuku(q, b1, temp );

		cout << "-------------------" << endl;
		cout << "1. Kembali ke menu utama " << endl;
		int pil23;
		cout << "Input : " ; cin >>pil23;
		if (pil23 == 1) {
			goto menu;
		} 

	} else if (pilihan == 6) {
	    tumpuk.top=-1;
	    char dt[10];
	    do{
			KeluarAntrianPengembalian(qp);
		    cout<<"\n1. Menerima buku\n";
		    cout<<"2. Menata buku\n";
		    cout<<"3. Menampilkan data yang ditumpuk\n";
		    cout<<"4. Keluar\n";
		    cout<<"\nPilihan: "; cin>>pil;
		    switch (pil)
		    {
		    case 1:
			    if(tumpuk.top !=max_size-1){
				    cout<<"\nJudul buku= ";cin>>dt;
				    tumpuk.top++;
				    strcpy(tumpuk.data[tumpuk.top],dt);
			    }
			    else cout<<"\nSudah penuh!\n";
			        break;
		    case 2:
			    if(tumpuk.top > -1){
				    for(int i=0; i<=tumpuk.top; i++){
					    cout<<"\nData yang diambil= "<<tumpuk.data[tumpuk.top];
					    tumpuk.top--;
				}
			    }else cout<<"\nTumpukan kosong\n";
			        break;
		    case 3:
                system("cls");
			    if(tumpuk.top>-1){
				    cout<<"=========================="<<endl;
      			    cout<<"|   No   |   Nama Buku    |"<<endl;
      			    cout<<"=========================="<<endl;
				    for(int i=0; i<=tumpuk.top; i++){
					    cout<<"| " <<i+1  << "      | " << tumpuk.data[i]<<"         |" <<endl;
				    }
				    cout<<"=========================="<<endl;
			    }else cout<<"\nTumpukan kosong\n";
			        break;
		        }
	        }while(pil !=4);
		        goto menu;
	} else if (pilihan == 0) {
		return 0;
	}
}

// Berikut adalah beberapa fungsi.....

void inputbuku(databuku& b1) {
	system("cls");
	cout<<"Masukan id buku : ";
	cin>>b1.idbuku;
	cin.ignore();
	cout<<"Masukan judul buku : ";
	getline(cin, b1.judulbuku);
	cout<<"Masukan nama pengarang : ";
	getline(cin, b1.namapengarang);
	cout<<"Masukan tahun terbit : ";
	cin>>b1.thterbit;
	cout<<"Masukan Buku yang tersedia : ";
	cin>>b1.jumlahbuku;
	b1.pinjam = false;
}

void simpan(databuku b1[] , int& temp) {
	if (temp < max_size){
		inputbuku(b1[temp]);
		temp++;
		system("cls");
        cout << "SILAHKAN DI TUNGGU SEBENTAR";
        cout << endl << endl;
        cout << "---"; sleep (1) ; cout << "---"; sleep (1) ; cout << "---"; sleep (1) ;
        system("cls");
		cout << "Data Buku Berhasil disimpan" << endl;
	} else {
		cout << "Buku tidak dapat di simpan " << endl;
	}
}

void sortdatabuku(databuku b1[], int temp) {
	const int idWidth = 5;
    const int judulWidth = 30;
    const int pengarangWidth = 15;
    const int tahunWidth = 13;
    const int stokWidth = 7;

	cout << setw(idWidth) << left << "|  Id  ";
    cout << setw(judulWidth) << left << "| Judul ";
    cout << setw(pengarangWidth) << left << "| Nama Pengarang";
    cout << setw(tahunWidth) << left << "| Tahun Terbit  ";
    cout << setw(stokWidth) << left << "| Stok  |" << endl;

	cout << setw(idWidth + judulWidth + pengarangWidth + tahunWidth + stokWidth + 23) << setfill('-') << "-" << setfill(' ') << endl;

    for (int i = 0; i < temp - 1; i++) {
    		for (int j = 0; j < temp - i - 1; j++) {
        			if (b1[j].idbuku > b1[j + 1].idbuku) {
            				databuku temp = b1[j];
            				b1[j] = b1[j + 1];
            				b1[j + 1] = temp;
					}
			}
		}
		for (int j = 0; j < temp; j++) {
    	cout << "|  " << setw(idWidth - 2) << left << b1[j].idbuku;
        cout << "| " << setw(judulWidth - 1) << left << b1[j].judulbuku;
        cout << "| " << setw(pengarangWidth - 1) << left << b1[j].namapengarang;
        cout << "| " << setw(tahunWidth - 1) << left << b1[j].thterbit;
        cout << "| " << setw(stokWidth - 1) << left << b1[j].jumlahbuku << " |" << endl;
    }
}

void MasukAntrian(queuepinjam& q) {
    if (!full(q)) {
        q.ekor++;
        q.nomor[q.ekor] = q.ekor + 1;
        cout << "Masukkan Nama Anda : ";
        cin >> q.namaanggota[q.ekor];
            
        system("cls");
        cout << "SILAHKAN DI TUNGGU SEBENTAR";
        cout << endl << endl;
        cout << "---"; sleep (1) ; cout << "---"; sleep (1) ; cout << "---"; sleep (1) ;
        system("cls");
        cout << "---------------------------" << endl;
        cout << "Anda Telah Memiliki Nomer Antrian Peminjaman!!" << endl;
        cout << "Nomer Antrian Anda = " << q.nomor[q.ekor] << endl;
        cout << "Silahkan Menunggu Antriannya Agar Anda Dapat Meminjam Buku!!!" << endl;
        cout << "---------------------------" << endl;
        cout << "-------------------" << endl;
		cout << "1. Menambah Antrian Peminjaman " << endl;
		cout << "2. Kembali ke menu utama " << endl;
		cout << "Input : " ; 

        } else {
            cout << "Data penuh";
        }
}


void MasukAntrianPengembalian(queuepengembalian& qp) {
    if (!fullpengembalian(qp)) {
        qp.ekorpengembalian++;
        qp.nomorpgl[qp.ekorpengembalian] = qp.ekorpengembalian + 1;
        cout << "Masukkan Nama Anda : ";
        cin >> qp.namaanggotapgl[qp.ekorpengembalian];
            
        system("cls");
        cout << "SILAHKAN DI TUNGGU SEBENTAR";
        cout << endl << endl;
        cout << "---"; sleep (1) ; cout << "---"; sleep (1) ; cout << "---"; sleep (1) ;
        system("cls");
        cout << "---------------------------" << endl;
        cout << "Anda Telah Memiliki Nomer Antrian Pengembalian Buku!!" << endl;
        cout << "Nomer Antrian Anda = " << qp.nomorpgl[qp.ekorpengembalian] << endl;
        cout << "Silahkan Menunggu Antriannya Agar Anda Dapat Mengembalikan Buku!!!" << endl;
        cout << "---------------------------" << endl;
        cout << "-------------------" << endl;
		cout << "1. Menambah Antrian Pengembalian " << endl;
		cout << "2. Kembali ke menu utama " << endl;
		cout << "Input : " ; 

        } else {
            cout << "Data Antrian Penuh";
        }
}


void KeluarAntrian(queuepinjam& q) {
    if (!empty(q)) {
        cout << "Nomor Antrian  : " << q.nomor[0] << endl;
        cout << "Atas nama      : " << q.namaanggota[0] << endl;
        for (int i = 1; i <= q.ekor; i++) {
                q.namaanggota[i - 1] = q.namaanggota[i];
                q.nomor[i - 1] = q.nomor[i];
        }
            q.ekor--;   
        } else {
            cout << "Data kosong";
        }
}


void KeluarAntrianPengembalian(queuepengembalian& qp) {
    if (!emptypengembalian(qp)) {
        cout << "Panggilan Nomor Antrian Pengembalian : " << qp.nomorpgl[0] << endl;
        cout << "Atas nama                            : " << qp.namaanggotapgl[0] << endl;
        for (int i = 1; i <= qp.ekorpengembalian; i++) {
                qp.namaanggotapgl[i - 1] = qp.namaanggotapgl[i];
                qp.nomorpgl[i - 1] = qp.nomorpgl[i];
        }
            qp.ekorpengembalian--;   
        } else {
            cout << "Data kosong";
        }
}

void caridanTampilBuku(const databuku b1[], int temp, const string& cariBuku) {
	int indeksBuku = -1;

    for (int i = 0; i < temp; ++i) {
        if (b1[i].judulbuku.find(cariBuku) != string::npos) {
            indeksBuku = i;
            break;
        }
    }
    if (indeksBuku != -1) {
        cout << "\nBuku ditemukan!\n";
        cout << "Judul: " << b1[indeksBuku].judulbuku << endl;
        cout << "Pengarang: " << b1[indeksBuku].namapengarang << endl;
        cout << "Tahun Terbit: " << b1[indeksBuku].thterbit << endl;
    } else {
        cout << "\nBuku tidak ditemukan.\n";
    }
}

void peminjamanbuku(queuepinjam& q, databuku b1[], int temp) {
    int noantrian = !empty(q) ? q.nomor[0] : -1;
    string namaantrian = !empty(q) ? q.namaanggota[0] : "Tidak Ada Antrian";

    if (noantrian != -1) {
        cout << "Nomor Antrian Anda  : " << noantrian << endl;
        cout << "Nama Antrian        : " << namaantrian << endl;

        int nobuku;

            cout << "Masukkan ID Buku yang Ingin Dipinjam: ";
            cin >> nobuku;

            bool validID = false;
            for (int i = 0; i < temp; ++i) {
                if (b1[i].idbuku == nobuku && b1[i].jumlahbuku > 0) {
                    validID = true;
                    q.bkPinjam[noantrian - 1] = &b1[i];
                    q.bkPinjam[noantrian - 1]->pinjam = true;
                    q.bkPinjam[noantrian - 1]->jumlahbuku--;
                    cout << "Buku ID " << nobuku << " berhasil dipinjam!" << endl;
                    break;
                }
            }

            if (!validID) {
                cout << "ID Buku tidak valid atau buku tidak tersedia." << endl;
            }

        KeluarAntrian(q);

    } else {
        cout << "Antrian kosong. Harap mengambil nomor antrian terlebih dahulu." << endl;
    }
}
