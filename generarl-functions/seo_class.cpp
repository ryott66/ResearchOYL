#include "seo_class.hpp"
    // 静的カウンタの初期化
    int SEO::idCounter = 0;

    // コンストラクタ（パラメータの初期設定）
    SEO::SEO() :R(0), Rj(0), Cj(0), C(0), Vd(0), Q(0), Vn(0), legs(0) {
        dE["up"] = 0.0;
        dE["down"] = 0.0;
        wt["up"] = 0.0;
        wt["down"] = 0.0;
        tunnel = "";
    }

    SEO::SEO(double r, double rj, double cj, double c, double vd, int legscounts)
        : R(r), Rj(rj), Cj(cj), C(c), Vd(vd), Q(0.0), Vn(0.0), legs(legscounts), 
        V(legscounts, 0.0), q(legscounts, 0.0),connection(legscounts, 0){
        id = idCounter++;
        dE["up"] = 0.0;
        dE["down"] = 0.0;
        wt["up"] = 0.0;
        wt["down"] = 0.0;
        tunnel = "";
        // cout << "SEO object created." << endl;
    }

    //-----------セッター------------//
    // バイアス電圧を設定
    void SEO::setVias(const double vd) {
        Vd = vd;
    }

    // 接続情報を設定
    void SEO::setConnections(const vector<int>& connections) {
        if (connections.size() != legs) {
            throw invalid_argument("The size of connections must match the number of legs.");
        }
        connection = connections;
    }

    // 周囲の電圧を設定
    void SEO::setSurroundingVoltages(const vector<SEO>& SEOs) {
        if (connection.size() != legs) {
            throw invalid_argument("The number of legs does not match the connection size.");
        }

        for (size_t i = 0; i < connection.size(); i++) {
            int connectedID = connection[i];  // 接続されている素子のID
            if (connectedID >= SEOs.size() || connectedID < 0) {
                throw out_of_range("Invalid connection ID.");
            }
            V[i] = SEOs[connectedID].getNodeVoltage();  // 接続先のVnを取得して設定
        }
    }

    //-----------ゲッター------------//
    // IDを取得
    int SEO::getID() const {
        return id;
    }
    
    // ノード電圧を取得
    double SEO::getNodeVoltage() const {
        return Vn;
    }


    // 電荷の更新
    void SEO::updateCharge(double dt) {
        Q += dt * (Vd - Vn) / R;
    }

    // ノード電圧の計算
    void SEO::calculateNodeVoltage() {
        double totalQ = Q;
        for (const auto& v : V) {
            totalQ += C * v;
        }
        Vn = totalQ / Cj;
    }

    // エネルギー変化量の計算
    double SEO::calculateEnergyChange(bool isUp) const {
        return isUp ? e * (-e + 2 * Q) / (2 * (4 * C + Cj))
                    : -e * (e + 2 * Q) / (2 * (4 * C + Cj));
    }

    // トンネル待ち時間計算
    void SEO::calculateTunnelWt() {
        if (dE["up"] > 0) {
            wt["up"] = (e * e * Rj / dE["up"]) * log(1 / Random());
        }
        else{
            wt["up"] = 0;
        }
        if (dE["down"] > 0) {
            wt["down"] = (e * e * Rj / dE["up"]) * log(1 / Random());
        }
        else{
            wt["down"] = 0;
        }
    }

    //-------- 汎用処理 -------------//
    // 0から1の間の乱数を生成
    double SEO::Random() {
        static random_device rd;
        static mt19937 mt(rd());
        static uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(mt);
    }

    //-------- テスト用 -----------//
    // テスト用Rゲッター
    double SEO::getR() const{
        return R;
    }
    
    // テスト用Rjゲッター
    double SEO::getRj() const{
        return Rj;
    }
    
    // テスト用Cjゲッター
    double SEO::getCj() const{
        return Cj;
    }
    
    // テスト用Cゲッター
    double SEO::getC() const{
        return C;
    }

    // テスト用Vdゲッター
    double SEO::getVd() const{
        return Vd;
    }
    
    // テスト用legsゲッター
    int SEO::getlegs() const{
        return legs;
    }


    // テスト用idCounterゲッター
    int SEO::getidCounter() const {
        return idCounter;
    }
    // テスト用dEセッター
    void SEO::setdE(const string& direction, double value){
        dE[direction] = value;
    }

    // テスト用wtゲッター
    double SEO::getWT(const string& direction) const {
        auto it = wt.find(direction);
        if (it != wt.end()) {
            return it->second;
        }
        return 0.0;
    }

