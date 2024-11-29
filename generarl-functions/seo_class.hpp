#ifndef SEO_CLASS_HPP
#define SEO_CLASS_HPP

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
#include <random>


#define e 0.1602 // 電子の電荷

using namespace std;

class SEO {
private:
    int idCounter;   // 静的IDカウンタ
    int id;                 // ノードのID
    double Q;               // ノード電荷
    double Vn;              // ノード電圧
    double Vd;              // バイアス電圧
    const double R;         // 抵抗
    const double Rj;        // トンネル抵抗
    const double Cj;        // 接合容量
    const double C;         // 接続容量
    const int legs;         // 足の数
    vector<double> V;       // 周囲のノード電圧
    vector<double> q;       // 足の数に対応した接続キャパシタの電荷
    map<string, double> dE; // エネルギー変化量(up, down)
    map<string, double> wt; // トンネル待時間(up, down)
    string tunnel;          // トンネルの有無("", up, down)
    vector<int> connection; // 接続されている素子のID

public:
    // コンストラクタ（パラメータの初期設定）
    SEO(double r, double rj, double cj, double c, double vd, int legscounts);

    //-----------セッター------------//
    // idCounterを初期化
    void setidCounter();

    // バイアス電圧を設定
    void setVias(const double vd);

    // 接続情報を設定
    void setConnections(const vector<int>& connections);

    // 周囲の電圧を設定
    void setSurroundingVoltages(const vector<SEO>& SEOs);

    //-----------ゲッター------------//
    // IDを取得
    int getID() const;
    
    // ノード電圧を取得
    double getNodeVoltage() const;

    // 電荷の更新
    void updateCharge(double dt);

    // ノード電圧の計算
    void calculateNodeVoltage();

    // エネルギー変化量の計算
    double calculateEnergyChange(bool isUp) const;

    // トンネル待ち時間計算
    void calculateTunnelWt();

    //-------- 汎用処理 -------------//
    // 0から1の間の乱数を生成
    double Random();

    // テスト用
    // テスト用dEセッター
    void setdE(const string& direction, double value);

    // テスト用wtゲッター
    double getWT(const string& direction) const;
    
};

#endif // SEO_HPP
