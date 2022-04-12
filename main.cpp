#include <bit>
#include <bitset>
#include <iostream>
#include <string>

struct Couple {
    uint8_t group, skirt;
    std::string name;

    Couple(uint8_t group, uint8_t skirt, std::string name): group(group), skirt(skirt), name(std::move(name)) {}
};

Couple couples[24] = { // NOLINT(cert-err58-cpp)
        Couple(0, 1, "邢李沛沛 付洋"),
        Couple(0, 0, "吴茜 廖帷宇"),
        Couple(1, 1, "胡梦琳 梁恩广"),
        Couple(1, 0, "郭旻坤 申函宁"),
        Couple(1, 0, "花佳诚 夏雨"),
        Couple(1, 0, "阴柯宇 吴若愚"),
        Couple(1, 1, "刘志恒 王续颖"),
        Couple(1, 0, "冯源 李朔瑾"),
        Couple(1, 2, "路超 龙江薇"),
        Couple(2, 1, "梁馨尹 金江禹"),
        Couple(1, 0, "伏开笛 刘佳璇"),
        Couple(0, 1, "李冬瑞 李鸿磊"),
        Couple(1, 1, "许铠铄 张洋"),
        Couple(0, 1, "翁颢洋 陈雨欣"),
        Couple(0, 1, "吕钊阳 来瑛"),
        Couple(0, 1, "刘泽川 杨艺昕"),
        Couple(1, 0, "王丹 彭盛飞"),
        Couple(0, 1, "樊若雨 张天婧"),
        Couple(0, 0, "丁冠乔 刘安琪"),
        Couple(0, 1, "樊卓帅 杨心怡"),
        Couple(2, 2, "许宜恒 何昀南"),
        Couple(2, 1, "何阳 周游"),
        Couple(1, 1, "郑凌翼 刘明宇"),
        Couple(0, 1, "梁瑞琦 吴柯锌")
};


int main() {
    uint32_t group_a = 0, group_b = 0, skirt_a = 0, skirt_b = 0;
    for (uint32_t i = 0; i < 24; ++ i) {
        if (couples[i].group == 0)
            group_a |= 1u << i;
        else if (couples[i].group == 1)
            group_b |= 1u << i;
        if (couples[i].skirt == 0)
            skirt_a |= 1u << i;
        else if (couples[i].skirt == 1)
            skirt_b |= 1u << i;
    }

    uint32_t max = 0, answer_group = 0, answer_skirt = 0;
    for (uint32_t group = 0; group < (1u << 24u); ++ group) {
        if (std::popcount(group) != 12)
            continue;
        for (uint32_t skirt = 0; skirt < 4; ++ skirt) {
            if ((skirt & 1) == (skirt >> 1))
                continue;

            uint32_t selected_group_a = group ^ ((1u << 24u) - 1u);
            uint32_t selected_group_b = group;
            uint32_t selected_skirt_a = 0, selected_skirt_b = 0;
            if ((skirt & 1) == 0)
                selected_skirt_a |= selected_group_a;
            if ((skirt >> 1) == 0)
                selected_skirt_a |= selected_group_b;
            if ((skirt & 1) == 1)
                selected_skirt_b |= selected_group_a;
            if ((skirt >> 1) == 1)
                selected_skirt_b |= selected_group_b;

            uint32_t satisfied = 0;
            satisfied += std::popcount(selected_group_a & group_a);
            satisfied += std::popcount(selected_group_b & group_b);
            satisfied *= 2;
            satisfied += std::popcount(selected_skirt_a & skirt_a);
            satisfied += std::popcount(selected_skirt_b & skirt_b);

            if (satisfied >= max)
                max = satisfied, answer_group = group, answer_skirt = skirt;
        }
    }

    for (auto& couple: couples) {
        if (couple.group == 2)
            max += 2;
        if (couple.skirt == 2)
            max += 1;
    }
    // std::cout << max << " (" << int(100.0 * max / 72.0) << "% satisfied), " << std::bitset<24>(answer_group) << ", " << std::bitset<2>(answer_skirt) << std::endl;
    std::cout << "Optimal solution: " << int(100.0 * max / 72.0) << "% satisfied" << std::endl;
    for (int i = 0; i < 24; ++ i) {
        uint8_t selected_group = (answer_group >> i) & 1;
        uint8_t selected_skirt = (answer_skirt >> selected_group) & 1;
        std::cout << " > " << couples[i].name
                  << ": Group " << (selected_group == 0 ? "A" : "B")
                  // << " (satisfied=" << (selected_group == couples[i].group or couples[i].group == 2) << ")"
                  << ", Skirt " << (selected_skirt == 0 ? "A" : "B")
                  // << " (satisfied=" << (selected_skirt == couples[i].skirt or couples[i].skirt == 2) << ")"
                  << std::endl;
    }
    return 0;
}
