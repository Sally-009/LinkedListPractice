#include <iostream>

using namespace std;

// int型ノード
struct Node{
    int data;       //ノードの中のデータ
    Node *link;     //次のノードのポインタ
};

/*
    NOTE:
    Node型ポインタ
    → 別に生成されたインスタンスを指す
    int型ポインタ
    → 生成されたインスタンス（自分自身）を指す
    
    リンクリストは"次の"ノードを指すからNode型を使う
*/

class LinkedList{
    
    private:
    Node *first;    // 最初のノードのアドレスをしまうポインタ
    int size;       // ノードのサイズ
    
    public:
    
    // コンストラクタ＆デストラクタ*************
    
    // 1. コンストラクタ
    /* 要素がゼロ（空っぽ）の状態にする */
    LinkedList(){ 
        first = nullptr;
        size = 0;
        /*
            NOTE:
            nullptr ... ポインタ用として厳密に定義されたNULL
            ポインターでNULLを使うときはこっちが安全！
        */
    }
    
    // 2. デストラクタ
    /* リストを最初から1つずつ全部消去する */
    ~LinkedList(){
        Node *p = first; // p = 現在地（ノードのアドレス）
        
        cout << "Destructor:" << endl;
        
        while(p != nullptr)    // 一番最後のlink(=nullptr)まで繰り返す
        {
            first = first->link;    // firstを、firstが指すノード（先頭）のlinkで上書きして更新
            cout<< p->data <<" deleted" << endl;    // この時点でノードはまだ実際に削除されていない
            delete p;   // ここでやっとメモリの開放（ノードの削除）がされる
            p=first;    // 空っぽになったpに次のノード（新たな先頭）のアドレスを再代入
        }
        
        size = 0;
    }
    
    // 基本的な処理*****************************
    
    /* 1. 一番後ろに新しいノードを追加する */
    void Append(int newData){
        
        // 新規ノードの作成
        Node *new_node = new Node;
        new_node -> data = newData; // データを格納
        new_node -> link = nullptr; // リンクは空（後の末尾）
        /*
            NOTE:
            Node new_node => ノードのアドレスを格納
            new Node      => ノードをインスタンス化 
        */
        
        // リストが空のとき → firstをこのノードのアドレスにする
        if(first == nullptr)
            first = new_node;
        // リストに要素があるとき
        else
        {
            // リストの末尾を探す（new_nodeはまだ連結していない状態）
            Node *current = first;  // current = 現在地（ノードのアドレス）
            while (current->link != nullptr)
                current = current->link;
                
            // 末尾のlink(nullptr)を新規ノードのアドレスにする（ノードを追加）
            current -> link = new_node;
        }
        
        // ノードが正しく追加されたことを表示
        cout << (new_node -> data) << " added" << endl;
        
        // サイズを1増やす
        size++;
    }
    
    /* 2. n番目のノードを削除する */
    void Delete(int n){
        Node *current = first;  // 現在地（ノードのアドレス）
        Node *previous = nullptr; // 削除するノードの前のノードのリンク書き換え用
        
        // nが有効か見る
        if(n > size)
        {
            cout << n << " is an invalid position." << endl;
            return;
        }
        else
        {
            // n番目のノードまで行く（n-1回またぐ）
            for(int i = 1; i < n; i++){
                previous = current;         //currentを上書きする前に保存しておく
                current = current->link;    //次のノードへ
            }
        }
        //リンクを更新してノードを削除
        //先頭が削除されるときはfirstを更新
        if(previous == nullptr)
            first = current->link;
        else
            previous->link = current->link; //前のノードと次のノードをリンクする
        
        cout << n << "th node:" << current->data << " deleted" << endl;   //削除されたことを表示
        delete current; // ノードを削除
        
        size--; // サイズを更新
    }
    
    /* 3. リストの内容を表示する */
    void Print(){
        Node *current = first;  // 現在地（ノードのアドレス）
        
        // データをアウトプットして次のリンク先へ
        while(current != nullptr)
        {
            cout << current->data << "-";
            current = current->link;
        }
        
        cout << endl;
    }
    
    // サイズを表示
    void PrintSize()
    {
        cout << "Size: " << size << endl;
    }
};


int main()
{
    int choice;
    bool err = false;
 
    LinkedList List;
    int size;
    int value;
    
    cout << "--Menu--" << endl;
    cout << "1. Enter values by user." << endl;
    cout << "2. Take a look without input." << endl;
    cout << "-----------------------------" << endl;
    do
    {
        cout << ">> ";
        cin >> choice;
        
        // エラーチェック
        if(choice != 1 && choice != 2)
        {
            cout << "Invalid Output!" << endl;
            err = true;
        }
        else
        err = false;
        
    }while(err == true);
    
    // 選択肢に応じて分岐
    switch(choice)
    {
        // 自分で入力する
        case 1:
            cout << "--Mode 1--" << endl;
            
            //リストに追加
            cout << "Enter the size of list: ";
            cin >> size;
            
            cout << "Enter integers: ";
            
            for(int i = 0; i < size; i++)
            {
                cin >> value;
                List.Append(value);
            }
            
            cout << endl;
            
            // リストを表示
            List.PrintSize();
            List.Print();
            
            cout << endl;
            
            // ノードを削除
            cout << "Enter the position to delete: ";
            cin >> value;
            
            List.Delete(value);
            
            cout << endl;
            
            // リストの表示
            List.PrintSize();
            List.Print();
            
            cout << endl;
            break;
        
        // あらかじめ用意した値を使う
        case 2:
            cout << "--Mode 2--" << endl;
            
            // リストに追加
            List.Append(2);
            List.Append(19);
            List.Append(32);
            List.Append(5);
            List.Append(88);
            
            cout << endl;

            // リストを表示
            List.PrintSize();
            List.Print();
            
            cout << endl;
            
            // ノードを削除
            List.Delete(3);     // Valid
            List.Delete(1);     // Valid
            List.Delete(10);    // Invalid
            
            cout << endl;
            
            // リストを表示
            List.PrintSize();
            List.Print();            
            
            cout << endl;
            
            break;
        
        default:
            break;
    }
    
    return 0;
}




