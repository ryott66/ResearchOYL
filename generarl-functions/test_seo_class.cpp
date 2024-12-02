#include<gtest/gtest.h>
#include "seo_class.hpp"

// テストケース: コンストラクタの動作確認
TEST(SEOTest, ConstructorCreatesIDs) {
    // 振動子のセットアップ
    int x = 2, y = 2, z = 2;
    vector<vector<vector<SEO>>> seoGrid(x, vector<vector<SEO>>(y, vector<SEO>(z)));

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                seoGrid.at(i).at(j).at(k) = SEO(1.0, 0.001, 18.0, 2.0, 0.007, 1);
            }
        }
    }
    // idの検証
    EXPECT_EQ(seoGrid.at(0).at(0).at(0).getID(), 0);
    EXPECT_EQ(seoGrid.at(1).at(1).at(1).getID(), 7);

    // パラメータの検証
    EXPECT_EQ(seoGrid.at(0).at(0).at(0).getR(), 1.0);
    EXPECT_EQ(seoGrid.at(0).at(0).at(0).getRj(), 0.001);
    EXPECT_EQ(seoGrid.at(0).at(0).at(0).getCj(), 18.0);
    EXPECT_EQ(seoGrid.at(0).at(0).at(0).getC(), 2);
    EXPECT_EQ(seoGrid.at(0).at(0).at(0).getVd(), 0.007);
    EXPECT_EQ(seoGrid.at(0).at(0).at(0).getlegs(), 1);
}

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