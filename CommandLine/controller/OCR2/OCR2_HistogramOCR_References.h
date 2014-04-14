#pragma once
#include <array>

// This file includes all the constant histogram average value's (Only used by the HistogramOCR class)
// Value's are obtained by testing

// Struct to store value's
struct PerfectAverages {
	const std::array<float, 5> Horizontal;
	const std::array<float, 5> Vertical;

	inline PerfectAverages(const std::array<float, 5> & Hori, const std::array<float, 5> & Verti) :
		Horizontal(Hori), Vertical(Verti) {}
};

// Declare Perfect Value's from Horizontal Averages per character
const std::array<float, 5> PerfectHoriAveragesChar0 = { .49f, .64f, .51f, .49f, .50f };
const std::array<float, 5> PerfectHoriAveragesChar1 = { .26f, .76f, .96f, 1.0f, 1.0f };
const std::array<float, 5> PerfectHoriAveragesChar2 = { .38f, .66f, .27f, .30f, .31f };
const std::array<float, 5> PerfectHoriAveragesChar3 = { .61f, .53f, .26f, .39f, .41f };
const std::array<float, 5> PerfectHoriAveragesChar4 = { .28f, .45f, .52f, .53f, .82f };
const std::array<float, 5> PerfectHoriAveragesChar5 = { .71f, .42f, .35f, .71f, .51f };
const std::array<float, 5> PerfectHoriAveragesChar6 = { .25f, .27f, .32f, .76f, .57f };
const std::array<float, 5> PerfectHoriAveragesChar7 = { .87f, .46f, .28f, .28f, .27f };
const std::array<float, 5> PerfectHoriAveragesChar8 = { .51f, .57f, .53f, .69f, .62f };
const std::array<float, 5> PerfectHoriAveragesChar9 = { .53f, .61f, .47f, .64f, .71f };
const std::array<float, 5> PerfectHoriAveragesChara = { .24f, .38f, .42f, .42f, .77f };
const std::array<float, 5> PerfectHoriAveragesCharb = { .69f, .62f, .52f, .82f, .70f };
const std::array<float, 5> PerfectHoriAveragesCharc = { .59f, .60f, .30f, .28f, .27f };
const std::array<float, 5> PerfectHoriAveragesChard = { .62f, .60f, .48f, .46f, .48f };
const std::array<float, 5> PerfectHoriAveragesChare = { .83f, .64f, .28f, .74f, .63f };
const std::array<float, 5> PerfectHoriAveragesCharf = { .88f, .67f, .29f, .29f, .46f };
const std::array<float, 5> PerfectHoriAveragesCharg = { .53f, .49f, .26f, .24f, .63f };
const std::array<float, 5> PerfectHoriAveragesCharh = { .44f, .49f, .49f, .89f, .71f };
const std::array<float, 5> PerfectHoriAveragesChari = { .57f, .91f, .93f, .83f, .93f };
const std::array<float, 5> PerfectHoriAveragesCharj = { .20f, .31f, .31f, .31f, .31f };
const std::array<float, 5> PerfectHoriAveragesChark = { .48f, .54f, .58f, .51f, .53f };
const std::array<float, 5> PerfectHoriAveragesCharl = { .25f, .29f, .29f, .29f, .29f };
const std::array<float, 5> PerfectHoriAveragesCharm = { .52f, .75f, .86f, .71f, .52f };
const std::array<float, 5> PerfectHoriAveragesCharn = { .48f, .63f, .72f, .74f, .75f };
const std::array<float, 5> PerfectHoriAveragesCharo = { .44f, .43f, .35f, .48f, .48f };
const std::array<float, 5> PerfectHoriAveragesCharp = { .68f, .68f, .52f, .64f, .67f };
const std::array<float, 5> PerfectHoriAveragesCharq = { .50f, .58f, .47f, .46f, .61f };
const std::array<float, 5> PerfectHoriAveragesCharr = { .51f, .57f, .49f, .71f, .66f };
const std::array<float, 5> PerfectHoriAveragesChars = { .59f, .54f, .28f, .49f, .42f };
const std::array<float, 5> PerfectHoriAveragesChart = { .89f, .43f, .25f, .25f, .25f };
const std::array<float, 5> PerfectHoriAveragesCharu = { .43f, .49f, .49f, .49f, .49f };
const std::array<float, 5> PerfectHoriAveragesCharv = { .43f, .47f, .48f, .47f, .48f };
const std::array<float, 5> PerfectHoriAveragesCharw = { .50f, .61f, .66f, .73f, .67f };
const std::array<float, 5> PerfectHoriAveragesCharx = { .45f, .50f, .47f, .31f, .41f };
const std::array<float, 5> PerfectHoriAveragesChary = { .46f, .50f, .49f, .40f, .25f };
const std::array<float, 5> PerfectHoriAveragesCharz = { .82f, .46f, .32f, .32f, .31f };
const std::array<float, 5> PerfectHoriAveragesChardash1 = { .00f, .00f, .00f, .00f, .00f };
const std::array<float, 5> PerfectHoriAveragesChardash2 = { .14f, .35f, .32f, .42f, .78f };

// Declare Perfect Value's from Vertical Averages per character
const std::array<float, 5> PerfectVertiAveragesChar0 = { .60f, .61f, .33f, .45f, .75f };
const std::array<float, 5> PerfectVertiAveragesChar1 = { .13f, .15f, .20f, .96f, .97f };
const std::array<float, 5> PerfectVertiAveragesChar2 = { .22f, .49f, .58f, .63f, .34f };
const std::array<float, 5> PerfectVertiAveragesChar3 = { .26f, .34f, .46f, .68f, .64f };
const std::array<float, 5> PerfectVertiAveragesChar4 = { .26f, .43f, .45f, .95f, .38f };
const std::array<float, 5> PerfectVertiAveragesChar5 = { .66f, .52f, .45f, .54f, .47f };
const std::array<float, 5> PerfectVertiAveragesChar6 = { .44f, .60f, .55f, .46f, .43f };
const std::array<float, 5> PerfectVertiAveragesChar7 = { .18f, .42f, .57f, .51f, .21f };
const std::array<float, 5> PerfectVertiAveragesChar8 = { .53f, .73f, .33f, .69f, .60f };
const std::array<float, 5> PerfectVertiAveragesChar9 = { .36f, .46f, .51f, .62f, .53f };
const std::array<float, 5> PerfectVertiAveragesChara = { .26f, .57f, .55f, .58f, .36f };
const std::array<float, 5> PerfectVertiAveragesCharb = { .98f, .62f, .51f, .79f, .47f };
const std::array<float, 5> PerfectVertiAveragesCharc = { .57f, .65f, .34f, .31f, .32f };
const std::array<float, 5> PerfectVertiAveragesChard = { .98f, .49f, .33f, .48f, .65f };
const std::array<float, 5> PerfectVertiAveragesChare = { .98f, .75f, .48f, .48f, .37f };
const std::array<float, 5> PerfectVertiAveragesCharf = { .98f, .68f, .31f, .32f, .23f };
const std::array<float, 5> PerfectVertiAveragesCharg = { .55f, .58f, .34f, .49f, .56f };
const std::array<float, 5> PerfectVertiAveragesCharh = { .98f, .39f, .16f, .31f, .98f };
const std::array<float, 5> PerfectVertiAveragesChari = { .97f, .98f, .98f, .98f, .65f };
const std::array<float, 5> PerfectVertiAveragesCharj = { .11f, .15f, .16f, .69f, .75f };
const std::array<float, 5> PerfectVertiAveragesChark = { .98f, .48f, .54f, .50f, .18f };
const std::array<float, 5> PerfectVertiAveragesCharl = { .98f, .62f, .16f, .16f, .16f };
const std::array<float, 5> PerfectVertiAveragesCharm = { .94f, .44f, .41f, .43f, .93f };
const std::array<float, 5> PerfectVertiAveragesCharn = { .98f, .51f, .33f, .45f, .98f };
const std::array<float, 5> PerfectVertiAveragesCharo = { .46f, .48f, .33f, .47f, .69f };
const std::array<float, 5> PerfectVertiAveragesCharp = { .98f, .48f, .27f, .42f, .41f };
const std::array<float, 5> PerfectVertiAveragesCharq = { .61f, .53f, .45f, .65f, .65f };
const std::array<float, 5> PerfectVertiAveragesCharr = { .98f, .40f, .46f, .69f, .40f };
const std::array<float, 5> PerfectVertiAveragesChars = { .40f, .58f, .50f, .57f, .41f };
const std::array<float, 5> PerfectVertiAveragesChart = { .15f, .30f, .98f, .23f, .13f };
const std::array<float, 5> PerfectVertiAveragesCharu = { .83f, .39f, .16f, .34f, .86f };
const std::array<float, 5> PerfectVertiAveragesCharv = { .27f, .57f, .43f, .62f, .27f };
const std::array<float, 5> PerfectVertiAveragesCharw = { .35f, .64f, .77f, .69f, .57f };
const std::array<float, 5> PerfectVertiAveragesCharx = { .25f, .63f, .47f, .63f, .42f };
const std::array<float, 5> PerfectVertiAveragesChary = { .15f, .37f, .66f, .44f, .20f };
const std::array<float, 5> PerfectVertiAveragesCharz = { .34f, .59f, .63f, .60f, .38f };
const std::array<float, 5> PerfectVertiAveragesChardash1 = { .14f, .17f, .17f, .17f, .17f };
const std::array<float, 5> PerfectVertiAveragesChardash2 = { .10f, .23f, .30f, .33f, .34f };

// Save Value's in struct
const PerfectAverages PerfectChar0(PerfectHoriAveragesChar0, PerfectVertiAveragesChar0);
const PerfectAverages PerfectChar1(PerfectHoriAveragesChar1, PerfectVertiAveragesChar1);
const PerfectAverages PerfectChar2(PerfectHoriAveragesChar2, PerfectVertiAveragesChar2);
const PerfectAverages PerfectChar3(PerfectHoriAveragesChar3, PerfectVertiAveragesChar3);
const PerfectAverages PerfectChar4(PerfectHoriAveragesChar4, PerfectVertiAveragesChar4);
const PerfectAverages PerfectChar5(PerfectHoriAveragesChar5, PerfectVertiAveragesChar5);
const PerfectAverages PerfectChar6(PerfectHoriAveragesChar6, PerfectVertiAveragesChar6);
const PerfectAverages PerfectChar7(PerfectHoriAveragesChar7, PerfectVertiAveragesChar7);
const PerfectAverages PerfectChar8(PerfectHoriAveragesChar8, PerfectVertiAveragesChar8);
const PerfectAverages PerfectChar9(PerfectHoriAveragesChar9, PerfectVertiAveragesChar9);
const PerfectAverages PerfectCharA(PerfectHoriAveragesChara, PerfectVertiAveragesChara);
const PerfectAverages PerfectCharB(PerfectHoriAveragesCharb, PerfectVertiAveragesCharb);
const PerfectAverages PerfectCharC(PerfectHoriAveragesCharc, PerfectVertiAveragesCharc);
const PerfectAverages PerfectCharD(PerfectHoriAveragesChard, PerfectVertiAveragesChard);
const PerfectAverages PerfectCharE(PerfectHoriAveragesChare, PerfectVertiAveragesChare);
const PerfectAverages PerfectCharF(PerfectHoriAveragesCharf, PerfectVertiAveragesCharf);
const PerfectAverages PerfectCharG(PerfectHoriAveragesCharg, PerfectVertiAveragesCharg);
const PerfectAverages PerfectCharH(PerfectHoriAveragesCharh, PerfectVertiAveragesCharh);
const PerfectAverages PerfectCharI(PerfectHoriAveragesChari, PerfectVertiAveragesChari);
const PerfectAverages PerfectCharJ(PerfectHoriAveragesCharj, PerfectVertiAveragesCharj);
const PerfectAverages PerfectCharK(PerfectHoriAveragesChark, PerfectVertiAveragesChark);
const PerfectAverages PerfectCharL(PerfectHoriAveragesCharl, PerfectVertiAveragesCharl);
const PerfectAverages PerfectCharM(PerfectHoriAveragesCharm, PerfectVertiAveragesCharm);
const PerfectAverages PerfectCharN(PerfectHoriAveragesCharn, PerfectVertiAveragesCharn);
const PerfectAverages PerfectCharO(PerfectHoriAveragesCharo, PerfectVertiAveragesCharo);
const PerfectAverages PerfectCharP(PerfectHoriAveragesCharp, PerfectVertiAveragesCharp);
const PerfectAverages PerfectCharQ(PerfectHoriAveragesCharq, PerfectVertiAveragesCharq);
const PerfectAverages PerfectCharR(PerfectHoriAveragesCharr, PerfectVertiAveragesCharr);
const PerfectAverages PerfectCharS(PerfectHoriAveragesChars, PerfectVertiAveragesChars);
const PerfectAverages PerfectCharT(PerfectHoriAveragesChart, PerfectVertiAveragesChart);
const PerfectAverages PerfectCharU(PerfectHoriAveragesCharu, PerfectVertiAveragesCharu);
const PerfectAverages PerfectCharV(PerfectHoriAveragesCharv, PerfectVertiAveragesCharv);
const PerfectAverages PerfectCharW(PerfectHoriAveragesCharw, PerfectVertiAveragesCharw);
const PerfectAverages PerfectCharX(PerfectHoriAveragesCharx, PerfectVertiAveragesCharx);
const PerfectAverages PerfectCharY(PerfectHoriAveragesChary, PerfectVertiAveragesChary);
const PerfectAverages PerfectCharZ(PerfectHoriAveragesCharz, PerfectVertiAveragesCharz);
const PerfectAverages PerfectCharDash1(PerfectHoriAveragesChardash1, PerfectVertiAveragesChardash1);
const PerfectAverages PerfectCharDash2(PerfectHoriAveragesChardash2, PerfectVertiAveragesChardash2);