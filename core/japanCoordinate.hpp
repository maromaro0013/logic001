// 2014-12-03 y_ohta

#ifndef _JAPANCOODINATE_HPP_
#define _JAPANCOODINATE_HPP_

enum {
	ePREFNAME_HOKKAIDO = 0,
	ePREFNAME_AOMORI,
	ePREFNAME_IWATE,
	ePREFNAME_MIYAGI,
	ePREFNAME_AKITA,
	ePREFNAME_YAMAGATA,
	ePREFNAME_FUKUSHIMA,
	ePREFNAME_IBARAKI,
	ePREFNAME_TOCHIGI,
	ePREFNAME_GUNMA,
	ePREFNAME_SAITAMA,
	ePREFNAME_CHIBA,
	ePREFNAME_TOKYO,
	ePREFNAME_KANAGAWA,
	ePREFNAME_NIIGATA,
	ePREFNAME_TOYAMA,
	ePREFNAME_ISHIKAWA,
	ePREFNAME_FUKUI,
	ePREFNAME_YAMANASHI,
	ePREFNAME_NAGANO,
	ePREFNAME_GIFU,
	ePREFNAME_SHIZUOKA,
	ePREFNAME_AICHI,
	ePREFNAME_MIE,
	ePREFNAME_SHIGA,
	ePREFNAME_KYOTO,
	ePREFNAME_OSAKA,
	ePREFNAME_HYOGO,
	ePREFNAME_NARA,
	ePREFNAME_WAKAYAMA,
	ePREFNAME_TOTTORI,
	ePREFNAME_SHIMANE,
	ePREFNAME_OKAYAMA,
	ePREFNAME_HIROSHIMA,
	ePREFNAME_YAMAGUCHI,
	ePREFNAME_TOKUSHIMA,
	ePREFNAME_KAGAWA,
	ePREFNAME_EHIME,
	ePREFNAME_KOCHI,
	ePREFNAME_FUKUOKA,
	ePREFNAME_SAGA,
	ePREFNAME_NAGASAKI,
	ePREFNAME_KUMAMOTO,
	ePREFNAME_OITA,
	ePREFNAME_MIYAZAKI,
	ePREFNAME_KAGOSHIMA,
	ePREFNAME_OKINAWA,
	ePREFNAME_MAX
};

class japanCoodinate {
public:
	static double getLongitudeFromId(int id) {
		double prefLongitudeTable[ePREFNAME_MAX] = {
			141.4, 140.7, 141.2, 140.9, 140.1,
			140.4, 140.5, 140.5, 139.9, 139.1,
			139.7, 140.1, 139.7, 139.6, 139.0,
			137.2, 136.7, 136.2, 138.6, 138.2,
			136.7, 138.4, 136.9, 136.5, 135.9,
			135.8, 135.5, 135.2, 135.8, 135.2,
			134.2, 133.1, 133.9, 132.5, 131.5,
			134.6, 134.0, 132.8, 133.5, 130.4,
			130.3, 129.9, 130.7, 131.6, 131.4,
			130.6, 127.7
		};

		if (id < ePREFNAME_MAX && id > 0) {
			return prefLongitudeTable[id - 1];
		}
		return 0.0;
	}

	static double getLatitudeFromId(int id) {
		double prefLatitudeTable[ePREFNAME_MAX] = {
			43.1, 40.8, 39.7, 38.3, 39.7,
			38.2, 37.7, 36.4, 36.6, 36.4,
			35.9, 35.6, 35.7, 35.4, 37.9,
			36.7, 36.6, 36.1, 35.7, 36.6,
			35.4, 35.0, 35.1, 34.7, 35.0,
			35.0, 34.7, 34.7, 34.7, 34.2,
			35.5, 35.5, 34.7, 34.4, 34.2,
			34.1, 34.3, 33.8, 33.6, 33.6,
			33.2, 32.7, 32.8, 33.2, 31.9,
			31.6, 26.2
		};
		
		if (id < ePREFNAME_MAX && id > 0) {
			return prefLatitudeTable[id - 1];
		}
		return 0.0;
	}

	static int strToId(const char* prefStr) {
		const char* prefNames[ePREFNAME_MAX] = {
			"北海道", "青森", "岩手", "宮城", "秋田",
			"山形", "福島", "茨城", "栃木", "群馬",
			"埼玉", "千葉", "東京", "神奈川", "新潟",
			"富山", "石川", "福井", "山梨", "長野",
			"岐阜", "静岡", "愛知", "三重", "滋賀",
			"京都", "大阪", "兵庫", "奈良", "和歌山",
			"鳥取", "島根", "岡山", "広島", "山口",
			"徳島", "香川", "愛媛", "高知", "福岡",
			"佐賀", "長崎", "熊本", "大分", "宮崎",
			"鹿児島","沖縄"
		};

		for (int i = 0; i < ePREFNAME_MAX; i++) {
			if (strcmp(prefStr, prefNames[i]) == 0) {
				return i + 1;
			}
		}
		return ePREFNAME_MAX;
	}

	static double getLongitudeFromString(const char* prefStr) {
		return getLongitudeFromId(strToId(prefStr));
	}

	static double getLatitudeFromString(const char* prefStr) {
		return getLongitudeFromId(strToId(prefStr));
	}
};

#endif//_JAPANCOODINATE_HPP_