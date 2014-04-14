#include <array>

// This file includes all the constant intersection value's (Only used by the IntersectionOCR class)
// Value's are obtained by testing

// Struct to store value's
struct ReferenceIntersections {
	const std::array<int, 5> HorizontalIntersections;
	const std::array<int, 5> VerticalIntersections;

	inline ReferenceIntersections(const std::array<int, 5> & Hori, const std::array<int, 5> & Verti) :
		HorizontalIntersections(Hori), VerticalIntersections(Verti) {}
};

// Declarations
const std::array<int, 5> Hori0 = { 1, 2, 2, 2, 1 };
const std::array<int, 5> Verti0 = { 0, 1, 2, 1, 0 };
const ReferenceIntersections Intersections0(Hori0, Verti0);

const std::array<int, 5> Hori1 = { 1, 1, 1, 1, 1 };
const std::array<int, 5> Verti1 = { 0, 0, 1, 0, 0 };
const ReferenceIntersections Intersections1(Hori1, Verti1);

const std::array<int, 5> Hori2 = { 1, 1, 1, 1, 1 };
const std::array<int, 5> Verti2 = { 0, 2, 3, 2, 0 };
const ReferenceIntersections Intersections2(Hori2, Verti2);

const std::array<int, 5> Hori3 = { 2, 1, 1, 1, 1 };
const std::array<int, 5> Verti3 = { 0, 2, 3, 1, 0 };
const ReferenceIntersections Intersections3(Hori3, Verti3);

const std::array<int, 5> Hori4 = { 1, 1, 2, 1, 1 };
const std::array<int, 5> Verti4 = { 1, 1, 2, 1, 0 };
const ReferenceIntersections Intersections4(Hori4, Verti4);

const std::array<int, 5> Hori5 = { 1, 1, 2, 1, 1 };
const std::array<int, 5> Verti5 = { 0, 2, 3, 2, 0 };
const ReferenceIntersections Intersections5(Hori5, Verti5);

const std::array<int, 5> Hori6 = { 1, 1, 1, 2, 2 };
const std::array<int, 5> Verti6 = { 0, 2, 3, 2, 0 };
const ReferenceIntersections Intersections6(Hori6, Verti6);

const std::array<int, 5> Hori7 = { 1, 1, 1, 1, 1 };
const std::array<int, 5> Verti7 = { 0, 2, 2, 1, 0 };
const ReferenceIntersections Intersections7(Hori7, Verti7);

const std::array<int, 5> Hori8 = { 2, 2, 1, 2, 2 };
const std::array<int, 5> Verti8 = { 0, 1, 3, 1, 0 };
const ReferenceIntersections Intersections8(Hori8, Verti8);

const std::array<int, 5> Hori9 = { 1, 2, 1, 1, 1 };
const std::array<int, 5> Verti9 = { 0, 2, 3, 1, 0 };
const ReferenceIntersections Intersections9(Hori9, Verti9);

const std::array<int, 5> HoriA = { 1, 1, 2, 1, 2 };
const std::array<int, 5> VertiA = { 1, 1, 2, 1, 1 };
const ReferenceIntersections IntersectionsA(HoriA, VertiA);

const std::array<int, 5> HoriB = { 2, 2, 1, 2, 1 };
const std::array<int, 5> VertiB = { 0, 1, 3, 1, 0 };
const ReferenceIntersections IntersectionsB(HoriB, VertiB);

const std::array<int, 5> HoriC = { 1, 1, 1, 1, 1 };
const std::array<int, 5> VertiC = { 0, 1, 2, 2, 0 };
const ReferenceIntersections IntersectionsC(HoriC, VertiC);

const std::array<int, 5> HoriD = { 2, 2, 2, 2, 1 };
const std::array<int, 5> VertiD = { 1, 2, 2, 2, 1 };
const ReferenceIntersections IntersectionsD(HoriD, VertiD);

const std::array<int, 5> HoriE = { 1, 1, 1, 1, 1 };
const std::array<int, 5> VertiE = { 0, 1, 3, 2, 0 };
const ReferenceIntersections IntersectionsE(HoriE, VertiE);

const std::array<int, 5> HoriF = { 1, 1, 1, 1, 1 };
const std::array<int, 5> VertiF = { 0, 1, 2, 2, 0 };
const ReferenceIntersections IntersectionsF(HoriF, VertiF);

const std::array<int, 5> HoriG = { 1, 1, 1, 2, 1 };
const std::array<int, 5> VertiG = { 0, 2, 2, 3, 1 };
const ReferenceIntersections IntersectionsG(HoriG, VertiG);

const std::array<int, 5> HoriH = { 2, 2, 1, 2, 2 };
const std::array<int, 5> VertiH = { 0, 1, 1, 1, 0 };
const ReferenceIntersections IntersectionsH(HoriH, VertiH);

const std::array<int, 5> HoriI = { 1, 1, 1, 1, 1 };
const std::array<int, 5> VertiI = { 0, 0, 1, 0, 0 };
const ReferenceIntersections IntersectionsI(HoriI, VertiI);

const std::array<int, 5> HoriJ = { 1, 1, 1, 1, 1 };
const std::array<int, 5> VertiJ = { 0, 1, 1, 1, 0 };
const ReferenceIntersections IntersectionsJ(HoriJ, VertiJ);

const std::array<int, 5> HoriK = { 2, 1, 1, 2, 2 };
const std::array<int, 5> VertiK = { 1, 1, 2, 2, 0 };
const ReferenceIntersections IntersectionsK(HoriK, VertiK);

const std::array<int, 5> HoriL = { 1, 1, 1, 1, 1 };
const std::array<int, 5> VertiL = { 0, 1, 1, 1, 0 };
const ReferenceIntersections IntersectionsL(HoriL, VertiL);

const std::array<int, 5> HoriM = { 2, 2, 3, 3, 2 };
const std::array<int, 5> VertiM = { 1, 1, 1, 1, 1 };
const ReferenceIntersections IntersectionsM(HoriM, VertiM);

const std::array<int, 5> HoriN = { 2, 2, 3, 2, 2 };
const std::array<int, 5> VertiN = { 0, 1, 1, 1, 0 };
const ReferenceIntersections IntersectionsN(HoriN, VertiN);

const std::array<int, 5> HoriO = { 1, 2, 2, 2, 1 };
const std::array<int, 5> VertiO = { 0, 2, 2, 2, 1 };
const ReferenceIntersections IntersectionsO(HoriO, VertiO);

const std::array<int, 5> HoriP = { 2, 2, 2, 1, 1 };
const std::array<int, 5> VertiP = { 0, 1, 2, 1, 0 };
const ReferenceIntersections IntersectionsP(HoriP, VertiP);

const std::array<int, 5> HoriQ = { 1, 2, 2, 2, 1 };
const std::array<int, 5> VertiQ = { 1, 2, 2, 1, 0 };
const ReferenceIntersections IntersectionsQ(HoriQ, VertiQ);

const std::array<int, 5> HoriR = { 2, 2, 1, 2, 2 };
const std::array<int, 5> VertiR = { 1, 1, 2, 2, 0 };
const ReferenceIntersections IntersectionsR(HoriR, VertiR);

const std::array<int, 5> HoriS = { 1, 1, 1, 1, 1 };
const std::array<int, 5> VertiS = { 0, 2, 3, 2, 0 };
const ReferenceIntersections IntersectionsS(HoriS, VertiS);

const std::array<int, 5> HoriT = { 1, 1, 1, 1, 1 };
const std::array<int, 5> VertiT = { 0, 1, 1, 1, 0 };
const ReferenceIntersections IntersectionsT(HoriT, VertiT);

const std::array<int, 5> HoriU = { 2, 2, 2, 2, 1 };
const std::array<int, 5> VertiU = { 0, 1, 1, 1, 0 };
const ReferenceIntersections IntersectionsU(HoriU, VertiU);

const std::array<int, 5> HoriV = { 2, 2, 2, 1, 1 };
const std::array<int, 5> VertiV = { 1, 1, 1, 1, 0 };
const ReferenceIntersections IntersectionsV(HoriV, VertiV);

const std::array<int, 5> HoriW = { 3, 2, 1, 1, 2 };
const std::array<int, 5> VertiW = { 1, 1, 1, 1, 0 };
const ReferenceIntersections IntersectionsW(HoriW, VertiW);

const std::array<int, 5> HoriX = { 2, 1, 1, 1, 2 };
const std::array<int, 5> VertiX = { 1, 2, 1, 2, 0 };
const ReferenceIntersections IntersectionsX(HoriX, VertiX);

const std::array<int, 5> HoriY = { 2, 2, 1, 1, 1 };
const std::array<int, 5> VertiY = { 0, 1, 1, 1, 0 };
const ReferenceIntersections IntersectionsY(HoriY, VertiY);

const std::array<int, 5> HoriZ = { 1, 1, 1, 1, 1 };
const std::array<int, 5> VertiZ = { 0, 2, 3, 2, 0 };
const ReferenceIntersections IntersectionsZ(HoriZ, VertiZ);