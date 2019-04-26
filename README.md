# Soal Shift Modul 4

### List Soal
- [Soal 1](#Soal_1)
- [Soal 2](#Soal_2)
- [Soal 3](#Soal_3)
- [Soal 4](#Soal_4)
- [Soal 5](#Soal_5)

#### Soal 1
- Atta menginginkan nama file system yang akan kalian buat adalah “AFSHiaAP”, yang nama kepanjangannya adalah AHHA’s File System: Hierarchical and Advanced Protection. Berikut ini kebutuhan yang harus kalian penuhi:
Semua nama file dan folder harus terenkripsi
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:

	***qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0***

	Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:
“INI_FOLDER/halo” saat belum di-mount maka akan bernama “n,nsbZ]wio/QBE#”, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi “INI_FOLDER/halo” .
Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

    ###### Jawaban
    Pertama buat fungsi enkrip dahulu, saya memakai tipe char.  Fungsi enkrip ini berfungsi untuk mengembalikan hasil dekrip agar program dapat menemukan file/folder yang dimaksud. Berikut adalah fungsi enkripnya
	```c
	char *dec(const char *name, int key){
	char ch;
	char *res = (char*) malloc(sizeof(char));
	int len = strlen(name);
	for (int i=0; i <= len; ++i){
		ch = name[i];
		for (int j=1; j<=94;j++){
			if (name[i]==charlist[j]){
				int a = j;
				a = a + key;
				if(a>94){
					a = a-94;				
				}
				ch = charlist[a];
			}
		}
		res[i] = ch;
	}
	//printf("\n%s\n",name);
	//printf("%s\n",res);
	return res;
}
	```
	Berikut adalah funsi dekripnya
	```c
char *decc(const char *name, int key){
	char ch;
	char *res = (char*) malloc(sizeof(char));
	int len = strlen(name);
	for (int i=0; i <= len; ++i){
		ch = name[i];
		for (int j=1; j<=94;j++){
			if (name[i]==charlist[j]){
				int a = j;
				a = a - key;
				if(a<0){
					a = a+94;				
				}
				ch = charlist[a];
			}
		}
		res[i] = ch;
	}
	//printf("\n%s\n",name);
	//printf("%s\n",res);
	return res;
}
	```
	Path di enkrip di enkrip di xmp_getattr dan di bagian awal xmp_readdir untuk bisa mengembalikan nama file/folder agar bisa mencari file/folder yang dimaksud. Untuk mendekripnya dilakukan di dalam while di xmp_readdir untuk mengembalikan nama file/folder agar terbaca.

#### Soal 2
- Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos”
Urutan operasi dari kebutuhan ini adalah:
    A. Tepat saat sebelum file system di-mount
        Secara otomatis folder “Videos” terbuat di root directory file system
        Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”, “computer.mkv.001”, “computer.mkv.002”, dst. Maka secara otomatis file pecahan tersebut akan di-join menjadi file video “computer.mkv”. Untuk mempermudah kalian, dipastikan hanya video file saja yang terpecah menjadi beberapa file. File pecahan tersebut dijamin terletak di root folder fuse
       Karena mungkin file video sangat banyak sehingga mungkin saja saat menggabungkan file video, file system akan membutuhkan waktu yang lama untuk sukses ter-mount. Maka pastikan saat akan menggabungkan file pecahan video, file system akan membuat 1 thread/proses(fork) baru yang dikhususkan untuk menggabungkan file video tersebut
       Pindahkan seluruh file video yang sudah ter-join ke dalam folder “Videos”
       Jangan tampilkan file pecahan di direktori manapun
	
    B. Tepat saat file system akan di-unmount
         Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus file pecahan yang terdapat di root directory file system
         Hapus folder “Videos” 

#### Soal 3
- Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:
   - Owner Name 	: ‘chipset’ atau ‘ic_controller’
   - Group Name	: ‘rusak’
   - Tidak dapat dibaca
   
 Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.

   
#### Soal 4
- Pada folder YOUTUBER, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah “.iz1”. File berekstensi “.iz1” tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

#### Soal 5
- Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama Backup kemudian hasil dari save tersebut akan disimpan pada backup dengan nama namafile_[timestamp].ekstensi. Dan ketika file asli dihapus, maka akan dibuat folder bernama RecycleBin, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama namafile_deleted_[timestamp].zip dan ditaruh ke dalam folder RecycleBin (file asli dan backup terhapus). Dengan format [timestamp] adalah yyyy-MM-dd_HH:mm:ss
