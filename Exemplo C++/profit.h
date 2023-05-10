#pragma once

typedef struct
{
    wchar_t* ticker;
    wchar_t* bolsa;
    int feed;
} TAssetID;

////////////////////////////////////////////////////////////////////////////////
// WARNING: Não utilizar funções da dll dentro do CALLBACK
////////////////////////////////////////////////////////////////////////////////
//Callback do stado das diferentes conexões
typedef void(__stdcall* TStateCallback)(int nConnStateType, int nResult);

////////////////////////////////////////////////////////////////////////////////
//Callback  do estado do hystorico de ordens
typedef void(__stdcall* THistoryCallBack)(TAssetID AssetID,
    int nCorretora, int nQtd, int nTradedQtd, int nLeavesQtd, int Side,
    double sPrice, double sStopPrice, double sAvgPrice,
    __int64 nProfitID,
    wchar_t* TipoOrdem, wchar_t* Conta, wchar_t* Titular, wchar_t* ClOrdID, wchar_t* Status, wchar_t* Date);

typedef void(__stdcall* TProgressCallBack)(TAssetID assetId,
    int nProgress);

////////////////////////////////////////////////////////////////////////////////
//Callback de alterção em ordens
typedef void(__stdcall* TOrderChangeCallBack)(TAssetID AssetID,
    int nCorretora, int nQtd, int nTradedQtd, int nLeavesQtd, int Side,
    double sPrice, double sStopPrice, double sAvgPrice,
    __int64 nProfitID,
    wchar_t* TipoOrdem, wchar_t* Conta, wchar_t* Titular, wchar_t* ClOrdID, wchar_t* Status, wchar_t* Date, wchar_t* TextMessage);

////////////////////////////////////////////////////////////////////////////////
//Callback com a lista de contas
typedef void(__stdcall* TAccountCallback)(int nCorretora,
    wchar_t* CorretoraNomeCompleto, wchar_t* AccountID, wchar_t* NomeTitular);

////////////////////////////////////////////////////////////////////////////////
//Callback com informações marketData
typedef void(__stdcall* TNewTradeCallback)(TAssetID assetId,
    wchar_t* date,
    unsigned int nTradeNumber,
    double price, double vol,
    int qtd, int buyAgent, int sellAgent, int tradeType,
    wchar_t bIsEdit);

typedef void(__stdcall* THistoryTradeCallback)(TAssetID assetId,
    wchar_t* date,
    unsigned int nTradeNumber,
    double price, double vol,
    int qtd, int buyAgent, int sellAgent, int tradeType);

typedef void(__stdcall* TNewDailyCallback)(TAssetID TAssetIDRec,
    wchar_t* date,
    double sOpen, double sHigh, double sLow, double sClose, double sVol, double sAjuste, double sMaxLimit, double sMinLimit,
    double sVolBuyer, double sVolSeller, int nQtd, int nNegocios, int nContratosOpen, int nQtdBuyer, int nQtdSeller, int nNegBuyer, int nNegSeller);

typedef void(__stdcall* TChangeStateTicker)(TAssetID assetId, wchar_t* date, int nState);

typedef void(__stdcall* TTinyBookCallback)(TAssetID assetId, double price, int qtd, int side);

////////////////////////////////////////////////////////////////////////////////
//Callback com informações marketData

typedef void(__stdcall* TPriceBookCallback)(TAssetID assetId,
    int nAction, int nPosition, int Side, int nQtd, int nCount,
    double sPrice,
    void* pArraySell, void* pArrayBuy);

typedef void(__stdcall* TOfferBookCallback)(TAssetID assetId,
    int nAction, int nPosition, int Side, int nQtd, int nAgent, __int64 nOfferID,
    double sPrice,
    int bHasPrice, int bHasQtd, int bHasDate, int bHasOfferID, int bHasAgent,
    wchar_t* date,
    void* pArraySell, void* pArrayBuy);

typedef void(__stdcall* TNewTinyBookCallBack)(TAssetID assetId,
    double price,
    int qtd, int side);

typedef void(__stdcall* TChangeCotation)(TAssetID assetId, wchar_t* date, unsigned int nTradeNumber, double sPrice);

typedef void(__stdcall* TAssetListInfoCallback)(TAssetID assetId, wchar_t* strName, wchar_t* strDescription, int nMinOrderQtd, int nMaxOrderQtd, int nLote, int stSecurityType, int ssSecuritySubType, double sMinPriceIncrement, double sContractMultiplier, wchar_t* strDate, wchar_t* strISIN);
typedef void(__stdcall* TAssetListInfoCallbackV2)(TAssetID assetId, wchar_t* strName, wchar_t* strDescription, int nMinOrderQtd, int nMaxOrderQtd, int nLote, int stSecurityType, int ssSecuritySubType, double sMinPriceIncrement, double sContractMultiplier, wchar_t* strDate, wchar_t* strISIN, wchar_t* strSetor, wchar_t* strSubSetor, wchar_t* strSegmento);
typedef void(__stdcall* TAssetListCallback)(TAssetID assetId, wchar_t* strName);

typedef void(__stdcall* TAdjustHistoryCallback)(TAssetID assetId, double sValue, wchar_t* strAdjustType, wchar_t* strObserv, wchar_t* dtAjuste, wchar_t* dtDeliber, wchar_t* dtPagamento, int nAffectPrice);
typedef void(__stdcall* TAdjustHistoryCallbackV2)(TAssetID assetId, double sValue, wchar_t* strAdjustType, wchar_t* strObserv, wchar_t* dtAjuste, wchar_t* dtDeliber, wchar_t* dtPagamento, int nFlags, double dMult);
typedef void(__stdcall* TTheoreticalPriceCallback)(TAssetID assetId, double dTheoreticalPrice, __int64 nTheoreticalQtd);

////////////////////////////////////////////////////////////////////////////////
// Functions From ProfitDLL
typedef signed char(__stdcall* GetAllTicker)(const wchar_t* pwcBolsa);

typedef signed char(__stdcall* SetChangeCotationCallback)(TChangeCotation ChangeCotation);

typedef signed char(__stdcall* SetAssetListCallback)(TAssetListCallback AssetListCallback);
typedef signed char(__stdcall* SetAssetListInfoCallback)(TAssetListInfoCallback AssetListInfoCallback);
typedef signed char(__stdcall* SetAssetListInfoCallbackV2)(TAssetListInfoCallbackV2 AssetListInfoCallbackV2);
typedef signed char(__stdcall* SetAdjustHistoryCallback)(TAdjustHistoryCallback AdjustHistoryCallback);
typedef signed char(__stdcall* SetAdjustHistoryCallbackV2)(TAdjustHistoryCallbackV2 AdjustHistoryCallbackV2);
typedef signed char(__stdcall* SetChangeStateTickerCallback)(TChangeStateTicker ChangeState);
typedef signed char(__stdcall* SetTheoreticalPriceCallback)(TTheoreticalPriceCallback ChangeState);

typedef signed char(__stdcall* SetEnabledLogToDebug)(int bEnabled);

typedef signed char(__stdcall* DLLInitializeMarketLogin)(
    const wchar_t* activationKey,
    const wchar_t* user,
    const wchar_t* password,
    TStateCallback stateCallback,
    TNewTradeCallback newTradeCallback,
    TNewDailyCallback newDailyCallback,
    TPriceBookCallback priceBookCallback,
    TOfferBookCallback offerBookCallback,
    THistoryTradeCallback newHistoryCallback,
    TProgressCallBack progressCallBack,
    TNewTinyBookCallBack newTinyBookCallBack);


typedef signed char(__stdcall* DLLInitializeLogin) (
    const wchar_t* activationKey,
    const wchar_t* user,
    const wchar_t* password,
    TStateCallback stateCallback,
    THistoryCallBack historyCallBack,
    TOrderChangeCallBack orderChangeCallBack,
    TAccountCallback accountCallback,
    TNewTradeCallback newTradeCallback,
    TNewDailyCallback newDailyCallback,
    TPriceBookCallback priceBookCallback,
    TOfferBookCallback offerBookCallback,
    THistoryTradeCallback newHistoryCallback,
    TProgressCallBack progressCallBack,
    TNewTinyBookCallBack newTinyBookCallBack);

typedef signed char(__stdcall* Finalize)();

typedef signed char(__stdcall* SubscribeTicker)(const wchar_t* ticker, const wchar_t* bolsa);
typedef signed char(__stdcall* UnsubscribeTicker)(const wchar_t* ticker, const wchar_t* bolsa);
typedef signed char(__stdcall* SubscribePriceBook)(const wchar_t* ticker, const wchar_t* bolsa);
typedef signed char(__stdcall* UnsubscribePriceBook)(const wchar_t* ticker, const wchar_t* bolsa);
typedef signed char(__stdcall* SubscribeOfferBook)(const wchar_t* ticker, const wchar_t* bolsa);
typedef signed char(__stdcall* UnsubscribeOfferBook)(const wchar_t* ticker, const wchar_t* bolsa);

typedef wchar_t* (__stdcall* GetAgentNameByID)(int nID);
typedef wchar_t* (__stdcall* GetAgentShortNameByID)(int nID);

typedef signed char(__stdcall* FreePointer)(void* pointer, int nSize);

typedef signed char(__stdcall* SetServerAndPort)(wchar_t* server, wchar_t* port);
typedef signed char(__stdcall* GetServerClock)(double* serverClock, int* nYear, int* nMonth, int* nDay, int* nHour, int* nMin, int* nSec, int* nMilisec);

////////////////////////////////////////////////////////////////////////////////
// Roteamento
typedef __int64(__stdcall* SendBuyOrder)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* sSenha, wchar_t* pwcTicker, wchar_t* pwcBolsa, double sPrice, int nAmount);
typedef __int64(__stdcall* SendSellOrder)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* sSenha, wchar_t* pwcTicker, wchar_t* pwcBolsa, double sPrice, int nAmount);
typedef __int64(__stdcall* SendStopBuyOrder)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* sSenha, wchar_t* pwcTicker, wchar_t* pwcBolsa, double sPrice, double sStopPrice, int nAmount);
typedef __int64(__stdcall* SendStopSellOrder)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* sSenha, wchar_t* pwcTicker, wchar_t* pwcBolsa, double sPrice, double sStopPrice, int nAmount);
typedef __int64(__stdcall* SendZeroPosition)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* pwcTicker, wchar_t* pwcBolsa, wchar_t* pwcSenha, double sPrice);

typedef signed char(__stdcall* SendChangeOrder)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* sSenha, wchar_t* pwcClOrdId, double sPrice, int nAmount);
typedef signed char(__stdcall* SendCancelOrder)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* pwcClOrdId, wchar_t* sSenha);
typedef signed char(__stdcall* SendCancelOrders)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* pwcSenha, wchar_t* pwcTicker, wchar_t* pwcBolsa);
typedef signed char(__stdcall* SendCancelAllOrders)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* pwcSenha);

typedef signed char(__stdcall* GetAccount)();
typedef signed char(__stdcall* GetOrders)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* dateStart, wchar_t* dateEnd);
typedef signed char(__stdcall* GetOrder)(const wchar_t* pwcClOrdId);
typedef signed char(__stdcall* GetOrderProfitID)(__int64 nProfitID);
typedef void* (__stdcall* GetPosition)(const wchar_t* pwcIDAccount, const wchar_t* pwcIDCorretora, wchar_t* pwcTicker, wchar_t* pwcBolsa);
typedef signed char(__stdcall* GetHistoryTrades)(const wchar_t* pwcTicker, const wchar_t* bolsa, wchar_t* dateStart, wchar_t* dtDateEnd);

typedef signed char(__stdcall* SetDayTrade)(int bUseDayTrade);
typedef signed char(__stdcall* SetEnabledHistOrder)(int bEnabled);

typedef signed char(__stdcall* SubscribeAdjustHistory)(wchar_t* pwcTicker, wchar_t* bolsa);
typedef signed char(__stdcall* UnsubscribeAdjustHistory)(wchar_t* pwcTicker, wchar_t* bolsa);

typedef signed char(__stdcall* GetLastDailyClose)(wchar_t* ticker, wchar_t* bolsa, double* dClose, int bAdjusted);

// #Functions

//////////////////////////////////////////////////////////////////////////////
// Error Codes
const signed char NL_OK = 0;     // OK
//const signed char NL_LOGIN_INVALID = [1..4];  // LOGIN INVALID
const signed char NL_ERR_INIT = 80;             // Not initialized
const signed char NL_ERR_INVALID_ARGS = 90;     // Invalid arguments
const signed char NL_ERR_INTERNAL_ERROR = 100;  // Internal error
const signed char NL_WAITING_SERVER = 110;      // Waiting for server data

typedef struct {
    int day;
    int month;
    int year;
    int hour;
    int min;
    int sec;
    int mili;
} Date;

typedef struct {
    double   price;
    double   volume;
    int      qtd;
    wchar_t* asset;
    Date     date;
} Trade;

typedef struct {
    double open;
    double close;
    double max;
    double min;
    double volume;
    int    qtd;
    int    neg;
    Date   date;
    wchar_t* asset;
} TradeCandle;

typedef struct {
    int   length;
    char* data;
} String;

typedef struct {
    int corretora_id;
    String account_id;
    String titular;
    String ticker;
    int intraday_position;
    double price;
    double avg_sell_price;
    int sell_qtd;
    double avg_buy_price;
    int buy_qtd;
    int custody_d1;
    int custody_d2;
    int custody_d3;
    int blocked;
    int pending;
    int allocated;
    int provisioned;
    int qtd_position;
    int available;
} Position;