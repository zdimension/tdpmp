#include <iostream>
#include <fstream>
#include "Image.h"

int main()
{
    Image img;
    img.read("damier_propre_ascii.ppm");
    img.replace_color({0, 0, 0}, {255, 0, 0});
    img.write("damier_rouge.ppm");
    img.negate();
    img.write("damier_rouge_neg.ppm");

    img.read("Simspons.ppm");
    img.threshold(100);
    img.write("Simspons_bw.ppm");

    img.read("EU_propre_little.ppm");
    img.replace_color({0, 0, 128}, {255, 0, 0});
    img.write("EU_propre_little_rouge.ppm");

    img.read("Oeuvre_d_art.ppm");
    img.symmetry();
    img.write("Oeuvre_d_art_sym.ppm");

    std::cout << "Done" << std::endl;
    return 0;
}
