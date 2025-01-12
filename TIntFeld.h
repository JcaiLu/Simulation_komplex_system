//====================================================================
// Ost 14/15
//====================================================================
// Klasse TIntFeld
// periodische 1D/2D - Integer - Felder f�r Zellul�re Automaten
// Ost/TU BS 2014
//====================================================================
    //==== Anwendung:
    //
    // TIntFeld a,b,c;            Definitionen
    // TIntFeld d(10),e(10,10),
    // TIntFeld f(a) auch m�gl!
    //
    // int i = a.N                liefert Zeilenanzahl  (nur lesen)
    // int i = a.M                liefert Spaltenanzahl (nur lesen)
    //                            (nur lesen: a.N = 5 liefert Fehler)
    // int i = a.Size()           liefert abs. Groesse von a
    //                            (= a.N*a.M)
    // a.Size(10);                a: (10x1) Vektor
    // b.Size(10,10);             b: (10,10) Matrix
    // a = 0;                     alle Elemente = 0 (a(0)=0,..,a(9)=0)
    // int i = a(5) = 2;          Zugriff
    // int i = b(5,5) = 2;        Zugriff
    // b = a;                     Tiefe Kopie! (b wird 10x1 Vektor!)
    //
    // a.Read(Filename)           liest aus Fileame ein TIntFeld ein
    // a.Write(Filename)          schreibt a in File Filename
    // a.Read()                   wie oben mit Windows Opendialog
    // a.Write()                  wie oben mit Windows Savedialog
    //                            (Files haben Endung "*.int")
    //================================================================

#ifndef tif
#define tif

class TIntFeld {
    int *s, n, m;
public:
    TIntFeld(){s=0; n=m=0;}
    TIntFeld(int i){ s=0;n=m=0; Size(i);}
    TIntFeld(int i, int j){ s=0; n=m=0;; Size(i,j);}
    TIntFeld(const TIntFeld &t){ *this = t;}
    ~TIntFeld(){ if(s) delete [] s;}
    
    __property int N = { read = n};
    __property int M = { read = m};

    int &operator () (int i, int j=0){
        static int z = 0; if(!s) return z;
        i %=n; if(i<0) i+=n; j %=m; if(j<0) j+=m;
        return s[i*m+j];}
    TIntFeld &operator = (int i) {
        int k = n*m; while(k-->0) s[k] = i;
        return *this;}
    TIntFeld &operator = (TIntFeld &t){
        if((n!=t.n)||(m!=t.m)) Size(t.n,t.m);
        if(n*m) for(int j=0;j<n*m;j++) s[j]=t.s[j];
        return *this;}
    TIntFeld &operator = (const TIntFeld &t){
        if((n!=t.n)||(m!=t.m)) Size(t.n,t.m);
        if(n*m) for(int j=0;j<n*m;j++) s[j]=t.s[j];
        return *this;}

    int Size() { return n*m;}
    int Size(int i, int j = 1){
        if(s) delete [] s; n=m=0;
        if(i*j > 0) { s = new int [i*j]; n=i; m=j;}
        return n*m;}

   /* int Write(char *fn = 0){
        if(!s) return 0;
        ForceCurrentDirectory = true;
        PlanString Fn;
        if(!fn) {
            TSaveDialog *SD = new TSaveDialog(0);
            SD->DefaultExt = "*.int";
            SD->FileName = "Feld";
            SD->Options.Clear();
            SD->Options << ofNoChangeDir;
            SD->Filter = "TIntFeld-Datei (*.int)|*.int";
            SD->InitialDir =  "";
            SD->Title = "TIntFeld Objekt speichern";
            if(SD->Execute()) Fn = SD->FileName.c_str();}
        else Fn = fn;
        FILE *O = fopen(Fn.c_str(),"w+");
        if(O){
            int i,j;
            fprintf(O,"%d,%d",n,m);
            for(i=0;i<N;i++) {
                fprintf(O,"\n");
                for(j=0;j<M;j++) fprintf(O,"%d;",(*this)(i,j));}}
        fclose(O);
        return n*m;}

    int Read(char *fn=0){
        ForceCurrentDirectory = true;
        PlanString Fn;
        if(!fn) {
            TOpenDialog *OD = new TOpenDialog(0);
            OD->DefaultExt = "*.int";
            OD->FileName = "Feld";
            OD->Filter = "TIntFeld-Datei (*.int)|*.int";
            OD->Options.Clear();
            OD->Options << ofNoChangeDir;
            OD->InitialDir =  "";
            OD->Title = "TIntFeld Objekt einlesen";
            if(OD->Execute()) Fn = OD->FileName.c_str();}
        else Fn = fn;
        FILE *I = fopen(Fn.c_str(),"r");
        if(I){
            int i,j,k;
            fscanf(I,"%d,%d",&i,&j);
            Size(i,j);
            for(i=0;i<N;i++){
                fscanf(I,"\n");
                for(j=0;j<M;j++){
                    fscanf(I,"%d;",&k); (*this)(i,j) = k;}}}
        fclose(I);
        return n*m;}   */
};

#endif

