#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <cstdio>

using namespace std;

struct tugas{
    char matkul[50];
    char deskripsi[200];
    char deadline[20];
    char isDone[20];
};

enum MataKuliah {ALJABAR_LINEAR = 1, ANALISIS_KOMPLEKS, CAD, FISIKA_DASAR, KALKULUS, MEKANIKA_TEKNIK, PEMROGRAMAN_DASAR, TEKNOLOGI_MAJU, PRAKTIKUM_PENGUKURAN, NONE };

bool validasiTanggal(int &d, int &m, int &y){
    if(d < 1 || d > 31 || m < 1 || m > 12 || y != 2026 ){
        return false;
    }
    else{
        return true;
    }
}

vector<tugas> getTugas(fstream &myFile){
    vector<tugas> daftarTugas;
    tugas holdTugas;
    myFile.clear();
    myFile.seekg(0, ios::beg);
    while(myFile.read(reinterpret_cast<char*>(&holdTugas),sizeof(holdTugas))){
        daftarTugas.push_back(holdTugas);
    }
    return daftarTugas;
}

void writeData(fstream &myFile){
    int userInput, d = 0, m = 0, y = 0;
    tugas holdTugas;
    system("cls");
    cout << "Pilih Matakuliah\n"
            "1. Aljabar Linear\n"
            "2. Analisis Kompleks dan Deret\n"
            "3. Computer Aided Design\n"
            "4. Fisika Dasar\n"
            "5. Kalkulus\n"
            "6. Mekanika Teknik\n"
            "7. Pemrograman Dasar\n"
            "8. Pengantar Teknologi Maju\n"
            "9. Pengukuran Dasar (Praktikum)\n"
            "Pilih Mata Kuliah: ";
    cin >> userInput;

    switch(userInput){
        case ALJABAR_LINEAR:strncpy(holdTugas.matkul, "Aljabar Linear", 50); break;
        case ANALISIS_KOMPLEKS: strncpy(holdTugas.matkul, "Analisis Kompleks dan Deret", 50); break;
        case CAD: strncpy(holdTugas.matkul, "Computer Aided Design", 50); break;
        case FISIKA_DASAR: strncpy(holdTugas.matkul, "Fisika Dasar", 50); break;
        case KALKULUS: strncpy(holdTugas.matkul, "Kalkulus", 50); break;
        case MEKANIKA_TEKNIK: strncpy(holdTugas.matkul, "Mekanika Teknik", 50); break;  
        case PEMROGRAMAN_DASAR: strncpy(holdTugas.matkul, "Pemrograman Dasar", 50); break;  
        case TEKNOLOGI_MAJU: strncpy(holdTugas.matkul, "Pengantar Teknologi Maju", 50); break;
        case PRAKTIKUM_PENGUKURAN: strncpy(holdTugas.matkul, "Pengukuran Dasar (Praktikum)", 50); break;
    }
        
    cout << "Masukan Deskripsi: ";
    cin.ignore();
    cin.getline(holdTugas.deskripsi, 200);
    
    cout << "Masukan Deadline (dd-mm-yyyy): ";
    cin.getline(holdTugas.deadline,20);
    sscanf(holdTugas.deadline, "%d-%d-%d", &d, &m, &y);
    if(validasiTanggal(d,m,y)){
        strncpy(holdTugas.isDone, "Belum", 20);
        myFile.write(reinterpret_cast<char*>(&holdTugas), sizeof(holdTugas));
        cout << "Tugas Kamu berhasil ditambahkan" << endl;
    }
    else{
        cout << "Tugas kamu belum berhasil ditambahkan" << endl;
    }
}

void showTugas(vector<tugas> &daftar){
    system("cls");
    cout << left << setw(5) << "No"
         << setw(25) << "Matakuliah"
         << setw(35) << "Deskripsi"    
         << setw(15) << "Deadline"
         << setw(15) << "status" << endl;
    cout << string(100, '=') << endl;

    for(int i = 0; i < daftar.size(); i++){
    cout << left << setw(5) << i + 1
         << setw(25) << daftar[i].matkul
         << setw(35) << daftar[i].deskripsi
         << setw(15) << daftar[i].deadline
         << setw(15) << daftar[i].isDone << endl;
    }
}

void updateTugas(fstream &myFile, vector<tugas> &daftar){
    int userInput, userInput2, d = 0, m = 0, y = 0;;
    tugas holdTugas;

    cout << "Tugas mana yang ingin diselesaikan:";
    cin >> userInput;
    userInput -= 1;

    if (userInput >= 0 && userInput < daftar.size()){
        cout << "Menyelesaikan atau Edit \n"
             << "1. Menyelesaikan\n"
             << "2. Edit\n"
             << "Masukan Pilihan: ";
        cin >> userInput2;
        cin.ignore();
        if(userInput2 == 1){
            strncpy(daftar[userInput].isDone,"Selesai",20); 
            cout << "Tugas Berhasil diselesaikan" << endl;
        }
        else if (userInput2 == 2)
        {
            cout << "== UBAH DATA ==" << endl;
            cout << "Masukan Deskripsi Baru: ";
            cin.getline(daftar[userInput].deskripsi, 200);
            cout << "Masukan Deadline Baru (dd-mm-yyyy): ";
            cin.getline(daftar[userInput].deadline, 20);
            sscanf(daftar[userInput].deadline, "%d-%d-%d", &d, &m, &y);
            if(!(validasiTanggal)){
                cout << "Program anda tidak berhasil";
            }
            strncpy(daftar[userInput].isDone, "Belum", 20);
        }
        
        myFile.close();

        myFile.open("Database.bin", ios::out | ios::binary | ios::trunc);
        for(int i = 0; i < daftar.size(); i++){
            myFile.write(reinterpret_cast<char*>(&daftar[i]), sizeof(tugas));
        }
        myFile.close();
        myFile.open("Database.bin", ios::in | ios::out | ios::binary | ios::app);
    }
    else{
        cout << "Input yang anda masukan salah" << endl;
    }
}

void hapusTugas(fstream &myFile, vector<tugas> &daftar){
    int userInput;
    cout << "Mana yang ingin anda hapus: ";
    cin >> userInput;
    userInput -= 1;
    myFile.close();

    myFile.open("Database.bin", ios::out | ios::binary | ios::trunc);
    daftar.erase(daftar.begin() + userInput);
    for(int i = 0; i < daftar.size(); i++){
        myFile.write(reinterpret_cast<char*>(&daftar[i]), sizeof(tugas));
    }
    myFile.close();
    myFile.open("Database.bin", ios::in | ios::out | ios::binary | ios::app);
    cout << "Tugas sudah berhasil dihapus" << endl;
    
}

int main(){
    fstream myFile;
    int inputUser;
    bool isContinue = true;
    enum choice{create = 1, read, update, action_delete, keluar};
    
    while (isContinue)
    {
        system("cls");
        cout << "== CRUD TUGAS ==" << endl;
        cout << "1. Tambah Tugas" << endl;
        cout << "2. Lihat Tugas" << endl;
        cout << "3. Selesaikan/Edit Tugas" << endl;
        cout << "4. Hapus Tugas" << endl;
        cout << "5. Keluar Program" << endl;
        cout << "Pilihan: ";
        cin >> inputUser;
        cin.ignore();
        myFile.open("Database.bin", ios::in | ios::out | ios::binary | ios::app);
        switch(inputUser){
        case create:
            writeData(myFile);
            system("pause");
            break;
        case read:{
            vector<tugas> daftar = getTugas(myFile);
            showTugas(daftar);
            system("pause");
            break;
        }
        case update:{
            vector<tugas> daftar = getTugas(myFile);
            showTugas(daftar);
            updateTugas(myFile, daftar);
            system("pause");
            break;
        }
        case action_delete:{
            vector<tugas> daftar = getTugas(myFile);
            showTugas(daftar);
            hapusTugas(myFile, daftar);
            system("pause");
            break;
        }
        case keluar:{
            cout << "Sampai Berjumpa lagi" << endl;
            isContinue = false;
            break;
        }

        myFile.close();
    }
    }
    
    
}   
