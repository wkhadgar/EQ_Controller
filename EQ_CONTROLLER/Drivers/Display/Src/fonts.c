#include "fonts.h"

const font_t fnt7x10 = {
        .width = 7,
        .height = 10,
        .BPC = 10,
        .scan = FONT_H,
        .min_char = 32,      /**< First character: ' ' */
        .max_char = 126,     /**< Last character: '~' */
        .unknown_char = 126, /**< Unknown character: '~' */
        .characters = {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//   (20)
                0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18,// ! (21)
                0x36, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// " (22)
                0x00, 0x36, 0x36, 0x7F, 0x7F, 0x36, 0x7F, 0x7F, 0x36, 0x36,// # (23)
                0x08, 0x3E, 0x6B, 0x0B, 0x0E, 0x38, 0x68, 0x6B, 0x3E, 0x08,// $ (24)
                0x67, 0x65, 0x37, 0x18, 0x18, 0x0C, 0x0C, 0x76, 0x53, 0x73,// % (25)
                0x00, 0x00, 0x00, 0x1E, 0x33, 0x33, 0x1E, 0x73, 0x33, 0x7E,// & (26)
                0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// ' (27)
                0x30, 0x18, 0x0C, 0x0C, 0x06, 0x06, 0x0C, 0x0C, 0x18, 0x30,// ( (28)
                0x06, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x18, 0x18, 0x0C, 0x06,// ) (29)
                0x00, 0x00, 0x08, 0x08, 0x7F, 0x1C, 0x1C, 0x36, 0x22, 0x00,// * (2A)
                0x00, 0x00, 0x18, 0x18, 0x7E, 0x7E, 0x18, 0x18, 0x00, 0x00,// + (2B)
                0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x38, 0x38, 0x18, 0x0C,// , (2C)
                0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00,// - (2D)
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3C, 0x18,// . (2E)
                0x40, 0x60, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x03, 0x01,// / (2F)
                0x1C, 0x36, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x36, 0x1C,// 0 (30)
                0x18, 0x1C, 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E,// 1 (31)
                0x3E, 0x63, 0x63, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x7F,// 2 (32)
                0x7F, 0x60, 0x30, 0x18, 0x3C, 0x60, 0x60, 0x60, 0x63, 0x3E,// 3 (33)
                0x30, 0x38, 0x3C, 0x36, 0x33, 0x33, 0x7F, 0x30, 0x30, 0x30,// 4 (34)
                0x7F, 0x03, 0x03, 0x3F, 0x67, 0x60, 0x60, 0x60, 0x63, 0x3E,// 5 (35)
                0x3C, 0x06, 0x03, 0x03, 0x3F, 0x67, 0x63, 0x63, 0x67, 0x3E,// 6 (36)
                0x7F, 0x60, 0x60, 0x30, 0x18, 0x18, 0x0C, 0x0C, 0x0C, 0x0C,// 7 (37)
                0x3E, 0x63, 0x63, 0x63, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x3E,// 8 (38)
                0x3E, 0x73, 0x63, 0x63, 0x73, 0x7E, 0x60, 0x60, 0x30, 0x1E,// 9 (39)
                0x00, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x00,// : (3A)
                0x00, 0x18, 0x3C, 0x18, 0x00, 0x3C, 0x38, 0x38, 0x18, 0x0C,// ; (3B)
                0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x60,// < (3C)
                0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00,// = (3D)
                0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x06,// > (3E)
                0x3E, 0x63, 0x63, 0x60, 0x30, 0x18, 0x18, 0x00, 0x18, 0x18,// ? (3F)
                0x00, 0x3E, 0x7F, 0x73, 0x7B, 0x4B, 0x4B, 0x7B, 0x07, 0x7E,// @ (40)
                0x1C, 0x3E, 0x63, 0x63, 0x63, 0x7F, 0x63, 0x63, 0x63, 0x63,// A (41)
                0x3F, 0x66, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x66, 0x66, 0x3F,// B (42)
                0x3E, 0x67, 0x63, 0x03, 0x03, 0x03, 0x03, 0x63, 0x67, 0x3E,// C (43)
                0x3F, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3F,// D (44)
                0x7F, 0x03, 0x03, 0x03, 0x1F, 0x03, 0x03, 0x03, 0x03, 0x7F,// E (45)
                0x7F, 0x03, 0x03, 0x03, 0x1F, 0x03, 0x03, 0x03, 0x03, 0x03,// F (46)
                0x3E, 0x63, 0x63, 0x03, 0x03, 0x03, 0x73, 0x63, 0x63, 0x3E,// G (47)
                0x63, 0x63, 0x63, 0x63, 0x7F, 0x63, 0x63, 0x63, 0x63, 0x63,// H (48)
                0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C,// I (49)
                0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x63, 0x63, 0x3E,// J (4A)
                0x63, 0x63, 0x33, 0x1B, 0x0F, 0x0F, 0x1B, 0x33, 0x63, 0x63,// K (4B)
                0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x43, 0x7F,// L (4C)
                0x63, 0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63, 0x63, 0x63,// M (4D)
                0x63, 0x63, 0x67, 0x67, 0x6F, 0x7B, 0x73, 0x73, 0x63, 0x63,// N (4E)
                0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E,// O (4F)
                0x3F, 0x63, 0x63, 0x63, 0x63, 0x3F, 0x03, 0x03, 0x03, 0x03,// P (50)
                0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7B, 0x3E, 0x60,// Q (51)
                0x3F, 0x63, 0x63, 0x63, 0x3F, 0x1F, 0x33, 0x33, 0x63, 0x63,// R (52)
                0x3E, 0x63, 0x63, 0x03, 0x3E, 0x60, 0x60, 0x63, 0x63, 0x3E,// S (53)
                0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,// T (54)
                0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E,// U (55)
                0x63, 0x63, 0x63, 0x63, 0x22, 0x36, 0x36, 0x1C, 0x1C, 0x08,// V (56)
                0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x6B, 0x6B, 0x7F, 0x36,// W (57)
                0x63, 0x63, 0x36, 0x36, 0x1C, 0x1C, 0x36, 0x36, 0x63, 0x63,// X (58)
                0x66, 0x66, 0x66, 0x3C, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18,// Y (59)
                0x7F, 0x60, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x03, 0x7F,// Z (5A)
                0x3E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x3E,// [ (5B)
                0x01, 0x03, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x60, 0x40,// \ (5C)
                0x3E, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3E,// ] (5D)
                0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// ^ (5E)
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,// _ (5F)
                0x3E, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00,// ° (60) [`]
                0x00, 0x00, 0x00, 0x3E, 0x60, 0x7E, 0x63, 0x63, 0x73, 0x6E,// a (61)
                0x03, 0x03, 0x03, 0x3B, 0x67, 0x63, 0x63, 0x63, 0x67, 0x3B,// b (62)
                0x00, 0x00, 0x00, 0x3E, 0x67, 0x03, 0x03, 0x03, 0x67, 0x3E,// c (63)
                0x60, 0x60, 0x60, 0x6E, 0x73, 0x63, 0x63, 0x63, 0x73, 0x6E,// d (64)
                0x00, 0x00, 0x00, 0x3E, 0x63, 0x63, 0x7F, 0x03, 0x63, 0x3E,// e (65)
                0x3C, 0x66, 0x06, 0x06, 0x06, 0x3F, 0x06, 0x06, 0x06, 0x06,// f (66)
                0x00, 0x00, 0x00, 0x7E, 0x33, 0x1E, 0x0F, 0x3E, 0x63, 0x3E,// g (67)
                0x03, 0x03, 0x03, 0x3B, 0x67, 0x63, 0x63, 0x63, 0x63, 0x63,// h (68)
                0x00, 0x18, 0x18, 0x00, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x3C,// i (69)
                0x00, 0x60, 0x60, 0x00, 0x70, 0x60, 0x60, 0x63, 0x63, 0x3E,// j (6A)
                0x03, 0x03, 0x03, 0x33, 0x1B, 0x0F, 0x0F, 0x1B, 0x33, 0x63,// k (6B)
                0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C,// l (6C)
                0x00, 0x00, 0x00, 0x36, 0x7F, 0x6B, 0x6B, 0x63, 0x63, 0x63,// m (6D)
                0x00, 0x00, 0x00, 0x3B, 0x67, 0x63, 0x63, 0x63, 0x63, 0x63,// n (6E)
                0x00, 0x00, 0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E,// o (6F)
                0x00, 0x00, 0x00, 0x3B, 0x67, 0x63, 0x67, 0x3B, 0x03, 0x03,// p (70)
                0x00, 0x00, 0x00, 0x6E, 0x73, 0x63, 0x73, 0x6E, 0x60, 0x60,// q (71)
                0x00, 0x00, 0x00, 0x3B, 0x67, 0x03, 0x03, 0x03, 0x03, 0x03,// r (72)
                0x00, 0x00, 0x00, 0x3E, 0x63, 0x06, 0x1C, 0x30, 0x63, 0x3E,// s (73)
                0x06, 0x06, 0x06, 0x06, 0x3F, 0x06, 0x06, 0x06, 0x66, 0x3C,// t (74)
                0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x73, 0x6E,// u (75)
                0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x36, 0x36, 0x1C,// v (76)
                0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x6B, 0x6B, 0x7F, 0x36,// w (77)
                0x00, 0x00, 0x00, 0x63, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x63,// x (78)
                0x00, 0x00, 0x00, 0x63, 0x63, 0x73, 0x6E, 0x60, 0x63, 0x3E,// y (79)
                0x00, 0x00, 0x00, 0x7F, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x7F,// z (7A)
                0x00, 0x78, 0x0C, 0x0C, 0x18, 0x0E, 0x18, 0x0C, 0x0C, 0x78,// { (7B)
                0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,// | (7C)
                0x00, 0x1E, 0x30, 0x30, 0x18, 0x70, 0x18, 0x30, 0x30, 0x1E,// } (7D)
                0x00, 0x4E, 0x7F, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ~ (7E)
        },
};


const font_t fnt5x7 = {
        .width = 5,
        .height = 7,
        .BPC = 5,
        .scan = FONT_V,
        .min_char = 32,      /**< First character: ' ' */
        .max_char = 126,     /**< Last character: '}' */
        .unknown_char = 126, /**< Unknown character: '~' */
        .characters = {
                0x00, 0x00, 0x00, 0x00, 0x00,// (space)
                0x00, 0x00, 0x5F, 0x00, 0x00,// !
                0x00, 0x07, 0x00, 0x07, 0x00,// "
                0x14, 0x7F, 0x14, 0x7F, 0x14,// #
                0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
                0x23, 0x13, 0x08, 0x64, 0x62,// %
                0x36, 0x49, 0x55, 0x22, 0x50,// &
                0x00, 0x05, 0x03, 0x00, 0x00,// '
                0x00, 0x1C, 0x22, 0x41, 0x00,// (
                0x00, 0x41, 0x22, 0x1C, 0x00,// )
                0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
                0x08, 0x08, 0x3E, 0x08, 0x08,// +
                0x00, 0x50, 0x30, 0x00, 0x00,// ,
                0x08, 0x08, 0x08, 0x08, 0x08,// -
                0x00, 0x60, 0x60, 0x00, 0x00,// .
                0x20, 0x10, 0x08, 0x04, 0x02,// /
                0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
                0x00, 0x42, 0x7F, 0x40, 0x00,// 1
                0x42, 0x61, 0x51, 0x49, 0x46,// 2
                0x21, 0x41, 0x45, 0x4B, 0x31,// 3
                0x18, 0x14, 0x12, 0x7F, 0x10,// 4
                0x27, 0x45, 0x45, 0x45, 0x39,// 5
                0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
                0x01, 0x71, 0x09, 0x05, 0x03,// 7
                0x36, 0x49, 0x49, 0x49, 0x36,// 8
                0x06, 0x49, 0x49, 0x29, 0x1E,// 9
                0x00, 0x36, 0x36, 0x00, 0x00,// :
                0x00, 0x56, 0x36, 0x00, 0x00,// ;
                0x00, 0x08, 0x14, 0x22, 0x41,// <
                0x14, 0x14, 0x14, 0x14, 0x14,// =
                0x41, 0x22, 0x14, 0x08, 0x00,// >
                0x02, 0x01, 0x51, 0x09, 0x06,// ?
                0x32, 0x49, 0x79, 0x41, 0x3E,// @
                0x7E, 0x11, 0x11, 0x11, 0x7E,// A
                0x7F, 0x49, 0x49, 0x49, 0x36,// B
                0x3E, 0x41, 0x41, 0x41, 0x22,// C
                0x7F, 0x41, 0x41, 0x22, 0x1C,// D
                0x7F, 0x49, 0x49, 0x49, 0x41,// E
                0x7F, 0x09, 0x09, 0x01, 0x01,// F
                0x3E, 0x41, 0x41, 0x51, 0x32,// G
                0x7F, 0x08, 0x08, 0x08, 0x7F,// H
                0x00, 0x41, 0x7F, 0x41, 0x00,// I
                0x20, 0x40, 0x41, 0x3F, 0x01,// J
                0x7F, 0x08, 0x14, 0x22, 0x41,// K
                0x7F, 0x40, 0x40, 0x40, 0x40,// L
                0x7F, 0x02, 0x04, 0x02, 0x7F,// M
                0x7F, 0x04, 0x08, 0x10, 0x7F,// N
                0x3E, 0x41, 0x41, 0x41, 0x3E,// O
                0x7F, 0x09, 0x09, 0x09, 0x06,// P
                0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
                0x7F, 0x09, 0x19, 0x29, 0x46,// R
                0x46, 0x49, 0x49, 0x49, 0x31,// S
                0x01, 0x01, 0x7F, 0x01, 0x01,// T
                0x3F, 0x40, 0x40, 0x40, 0x3F,// U
                0x1F, 0x20, 0x40, 0x20, 0x1F,// V
                0x7F, 0x20, 0x18, 0x20, 0x7F,// W
                0x63, 0x14, 0x08, 0x14, 0x63,// X
                0x03, 0x04, 0x78, 0x04, 0x03,// Y
                0x61, 0x51, 0x49, 0x45, 0x43,// Z
                0x00, 0x00, 0x7F, 0x41, 0x41,// [
                0x02, 0x04, 0x08, 0x10, 0x20,// "\"
                0x41, 0x41, 0x7F, 0x00, 0x00,// ]
                0x04, 0x02, 0x01, 0x02, 0x04,// ^
                0x40, 0x40, 0x40, 0x40, 0x40,// _
                0x00, 0x01, 0x02, 0x04, 0x00,// `
                0x20, 0x54, 0x54, 0x54, 0x78,// a
                0x7F, 0x48, 0x44, 0x44, 0x38,// b
                0x38, 0x44, 0x44, 0x44, 0x20,// c
                0x38, 0x44, 0x44, 0x48, 0x7F,// d
                0x38, 0x54, 0x54, 0x54, 0x18,// e
                0x08, 0x7E, 0x09, 0x01, 0x02,// f
                0x08, 0x14, 0x54, 0x54, 0x3C,// g
                0x7F, 0x08, 0x04, 0x04, 0x78,// h
                0x00, 0x44, 0x7D, 0x40, 0x00,// i
                0x20, 0x40, 0x44, 0x3D, 0x00,// j
                0x00, 0x7F, 0x10, 0x28, 0x44,// k
                0x00, 0x41, 0x7F, 0x40, 0x00,// l
                0x7C, 0x04, 0x18, 0x04, 0x78,// m
                0x7C, 0x08, 0x04, 0x04, 0x78,// n
                0x38, 0x44, 0x44, 0x44, 0x38,// o
                0x7C, 0x14, 0x14, 0x14, 0x08,// p
                0x08, 0x14, 0x14, 0x18, 0x7C,// q
                0x7C, 0x08, 0x04, 0x04, 0x08,// r
                0x48, 0x54, 0x54, 0x54, 0x20,// s
                0x04, 0x3F, 0x44, 0x40, 0x20,// t
                0x3C, 0x40, 0x40, 0x20, 0x7C,// u
                0x1C, 0x20, 0x40, 0x20, 0x1C,// v
                0x3C, 0x40, 0x30, 0x40, 0x3C,// w
                0x44, 0x28, 0x10, 0x28, 0x44,// x
                0x0C, 0x50, 0x50, 0x50, 0x3C,// y
                0x44, 0x64, 0x54, 0x4C, 0x44,// z
                0x00, 0x08, 0x36, 0x41, 0x00,// {
                0x00, 0x00, 0x7F, 0x00, 0x00,// |
                0x00, 0x41, 0x36, 0x08, 0x00,// }
                0x55, 0xAA, 0x55, 0xAA, 0x55 // unknown char (code 0x7E)
        },
};