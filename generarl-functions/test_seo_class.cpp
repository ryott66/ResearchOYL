#include<gtest/gtest.h>
#include "seo_class.hpp"

// テストケース: コンストラクタの動作確認
TEST(SEOTest, ConstructorCreatesIDs) {
    // 振動子のセットアップ
    // 3次元ベクトル (サイズ: 2x2x2) を動的に生成
    int x = 2, y = 2, z = 2;
    auto seoGrid = make_unique<vector<vector<vector<shared_ptr<SEO>>>>>(
        z, vector<vector<shared_ptr<SEO>>>(
               y, vector<shared_ptr<SEO>>(x)));
    // 各要素を生成して格納
    for (int i = 0; i < z; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < x; ++k) {
                (*seoGrid)[i][j][k] = make_shared<SEO>(1.0, 0.001, 18.0, 2.0, 0.007, 1);
            }
        }
    }
    // パラメータの検証
    EXPECT_EQ((*seoGrid).at(0).at(0).at(0)->getR(), 1.0);
    EXPECT_EQ((*seoGrid).at(0).at(0).at(1)->getRj(), 0.001);
    EXPECT_EQ((*seoGrid).at(0).at(1).at(0)->getCj(), 18.0);
    EXPECT_EQ((*seoGrid).at(1).at(0).at(0)->getC(), 2);
    EXPECT_EQ((*seoGrid).at(0).at(1).at(1)->getVd(), 0.007);
    EXPECT_EQ((*seoGrid).at(1).at(1).at(1)->getlegs(), 1);
}

// テストケース: 接続されてる振動子のポインタの追加確認

// テストケース: 接続されてる振動子のノード電圧を参照する動作確認

// テストケース: パラメータ計算の動作確認

// テストケース: calculateTunnelWt の動作確認
TEST(SEOTest, CalculateTunnelWt) {
    // 振動子のセットアップ
    SEO seo(1, 0.001, 18, 2, 0.007, 1);

    // エネルギー変化量をセット
    seo.setdE("up", 1);   // 上方向のエネルギー変化量
    seo.setdE("down", -1); // 下方向のエネルギー変化量

    // トンネル待ち時間を計算
    seo.calculateTunnelWt();
    // 結果を検証
    EXPECT_NE(seo.getWT("up"),0);
    EXPECT_EQ(seo.getWT("down"),0);

    // エネルギー変化量をセット
    seo.setdE("up", -1);   // 上方向のエネルギー変化量
    seo.setdE("down", 1); // 下方向のエネルギー変化量

    // トンネル待ち時間を計算
    seo.calculateTunnelWt();
    // 結果を検証
    EXPECT_EQ(seo.getWT("up"),0);
    EXPECT_NE(seo.getWT("down"),0);
}