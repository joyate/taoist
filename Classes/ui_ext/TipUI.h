#pragma once
#include "../data/GameData.h"
#include "extensions/cocos-ext.h"


USING_NS_CC_EXT;


/*
 * Tip ���
 */


class TipUI : public Node
{
public:
	TipUI(void);
	~TipUI(void);


	enum
	{
		DEFAULT_TIP_FONT_SIZE = 16,
	};



	static TipUI* create(const std::string& _bg_file, const Rect& capInset,int maxWidth = 150);



	/*
	 * @desc ����tip��ʾ�������Լ��ֺ�
	 * @param font_file ����·��
	 * @param font_size �����С
	 * @return
	 *	
	 */
	void setTipFont(const std::string& font_file, int font_size);


	/*
	 * @desc ���ɼ���tip��Ϣ
	 * @param _sk_id ����id
	 * @param _old_lv �ϼ��ܵȼ�
	 * @param _new_lv �¼��ܵȼ�
	 * @return
	 *	
	 */
	bool genSKillTipInfo(int _sk_id, int _old_lv, int _new_lv);



#ifdef _DEBUG

	void testTipUI();

#endif



	CREATE_FUNC(TipUI);

protected:

	//
	bool initFromFile(const std::string& _bg_file, const Rect& capInset, int maxWidth);


	// �Ű�tip��Ϣ
	void buildTipInfo();


	// ����tip��Ϣ����
	int calculateTipInfoLineCnt();


	//
	void addLine(const std::string& text,const Color4B& color);


private:

	// Scale9Sprite
	Node* m_bg;
	// Tips
	Vector<Node*> m_vec_tips;
	// ������󳤶�
	int m_maxWidth;


	std::string m_font_name;
	int m_font_size;

};

