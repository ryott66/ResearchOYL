#include<gtest/gtest.h>
#include "seo_class.hpp"

// テストケース: calculateTunnelWt の動作確認
TEST(SEOTest, CalculateTunnelWt) {
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