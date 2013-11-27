
class CDocumentData
{
public:
    CDocumentData( word::_Document* ifDoc )
        :m_ifDoc(ifDoc)
        ,m_hwnd(NULL)
    { }

    ~CDocumentData()
    { }

    HWND hwnd();

private:
    CComPtr<word::_Document> m_ifDoc;
    HWND m_hwnd;

public:
    std::vector<CComPtr<word::Range>> m_ifRosebudRanges;
};


class CDocumentDataManager
{
private:
    std::map<word::_Document*, std::unique_ptr<CDocumentData>> m_map;

public:
    CDocumentData* getDocumentData( word::_Document* ifDoc );
    void removeDocumentData( word::_Document* ifDoc );
};

