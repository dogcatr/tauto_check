#include <iostream>
#include <cmath>
#include <string>
#include "legalenum.h"
#include "legaltest.h"
#include "tauto.h"
#include "t_node.h"
#include "MainTest.h"
#include "itauto.h"
#include "Tableau.h"
#include "Tabenu.h"
#define rep(i,n) for(int i=0;i<n;i++)
using ll = long long;

int main()
{
    cout << "はじめに, 添付した説明書を読んでください." << endl;
    cout << "4が一番優れた判定を行います." << endl;
    cout << "legal formulaの列挙は, 0" << endl;//判定が正しく行われているかの確認用
    cout << "legal formulaの判定は, 1" << endl;//入力した文字列が論理式になっているか判定
    cout << "恒真性の判定は, 2" << endl;//遅い
    cout << "改良された恒真性の判定は, 3" << endl;//四角があると遅い
    cout << "一番早い恒真性の判定は, 4" << endl;//どの論理式も高速に判定できる. (確認した限りでは長さ20まで高速)
    string el;
    cin >> el;
    if (el == "0") {
        cout << "formulaの最大の長さを入力(計算量が爆発的に増加するため, 多くても10程度)" << endl;
        ll lenfml;
        cin >> lenfml;
        cout << "計算回数は" << (ll)((pow(Glencharset, lenfml + 1) - 1) / (Glencharset - 1)) << endl;
        cout << "以下の式はTをPropositionやFに置き換えてもlegalです." << endl;
        legalenum(lenfml);
    }
    else if (el == "1") {
        cout << "(,),S,N,A,O,-,>,T,Fと小文字アルファベットの文字列を入力してください. legal formulaであるか判定します." << endl;
        //cout << "ilegalの場合, 何も表示されません." << endl;
        std::string fml;
        cin >> fml;
        legaltest(fml);
    }
    else if (el == "2") {
        cout << "(,),S,N,A,O,-,>,T,Fと小文字アルファベットのformulaを入力してください. 恒真であるか判定します." << endl;
        cout << "恒真の場合, モデルの情報は与えられません. 恒真ではない場合, モデルの遷移関係と付値関数を出力します(カッコを含めて6文字程度にした方がよい)" << endl;
        cout << "formulaを入力してください: ";
        std::string fml;
        cin >> fml;
        tauto_test(fml);
    }
    else if (el == "3") {
        cout << "(,),S,N,A,O,-,>,T,Fと小文字アルファベットのformulaを入力してください. 恒真であるか判定します." << endl;
        cout << "Sを使う場合は長さを6文字程度にしてください." << endl;
        cout << "formulaを木に分解した後, 恒真の場合はtrue, 恒真でない場合, falseが表示されます." << endl;
        cout << "formulaを入力してください: ";
        std::string fml;
        cin >> fml;
        itauto_test(fml);
    }
    else if (el == "4") {
        //論理式を列挙してgameにかける
        cout << "(,),S,D,N,A,Oと小文字アルファベットのタブローゲーム用のformulaを入力してください. 恒真であるか判定します." << endl;

        std::string fml;
        cin >> fml;
        if (tableau_game(fml)) {
            cout << "恒真です\n";
        }
        else {
            cout << "タブロー用のformulaとしてilegalであるか, 恒真ではないです\n";
        }
        cout << "formulaとその恒真性の列挙をしますか? YesならY, NoならN: ";
        string s1;
        cin >> s1;
        cout << endl;
        if (s1 == "Y") {
            cout << "formulaの最大の長さを入力してください: ";
            int c1;
            cin >> c1;
            tabenu(c1);
        }
    }
    //system("pause");
    cout << "キーを押すと終了します" << endl;
    system("pause > NUL");
}