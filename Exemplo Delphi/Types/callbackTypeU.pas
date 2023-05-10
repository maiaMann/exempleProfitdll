unit callbackTypeU;

interface

uses
  structs;

type
// Callbacks //
  TStateCallback           = procedure                          (nStateType , nActResult : Integer) stdcall;

  THistoryCallback         = procedure                                         (rAssetID : TAssetIDRec;
                                        nCorretora , nQtd, nTradedQtd, nLeavesQtd, nSide : Integer;
                                                           sPrice, sStopPrice, sAvgPrice : Double;
                                                                               nProfitID : Int64;
                                        TipoOrdem, Conta, Titular, ClOrdID, Status, Date : PWideChar) stdcall;

  TOrderChangeCallback     = procedure                                         (rAssetID : TAssetIDRec;
                                        nCorretora , nQtd, nTradedQtd, nLeavesQtd, nSide : Integer;
                                                           sPrice, sStopPrice, sAvgPrice : Double;
                                                                               nProfitID : Int64;
                           TipoOrdem, Conta, Titular, ClOrdID, Status, Date, TextMessage : PWideChar) stdcall;

  TAccountCallback         = procedure                                       (nCorretora : Integer;
                                           CorretoraNomeCompleto, AccountID, NomeTitular : PWideChar) stdcall;

  TNewTradeCallback        = procedure                                       (rAssetID   : TAssetIDRec;
                                                                               pwcDate   : PWideChar;
                                                                          nTradeNumber   : Cardinal;
                                                                          sPrice, sVol   : Double;
                                               nQtd, nBuyAgent, nSellAgent, nTradeType   : Integer;
                                                                               bIsEdit   : Char) stdcall;

  TNewDailyCallback        = procedure                                         (rAssetID : TAssetIDRec;
                                                                                 pwcDate : PWideChar;
  sOpen, sHigh, sLow, sClose, sVol, sAjuste, sMaxLimit, sMinLimit, sVolBuyer, sVolSeller : Double;
           nQtd, nNegocios, nContratosOpen, nQtdBuyer, nQtdSeller, nNegBuyer, nNegSeller : Integer) stdcall;

  TPriceBookCallback       = procedure                                         (rAssetID : TAssetIDRec ;
                                                nAction , nPosition, Side, nQtds, nCount : Integer;
                                                                                  sPrice : Double;
                                                                   pArraySell, pArrayBuy : Pointer) stdcall;

  TOfferBookCallback       = procedure                                         (rAssetID : TAssetIDRec ;
                                                  nAction, nPosition, Side, nQtd, nAgent : Integer;
                                                                                nOfferID : Int64;
                                                                                  sPrice : Double;
                                    bHasPrice, bHasQtd, bHasDate, bHasOfferID, bHasAgent : Char;
                                                                                 pwcDate : PWideChar;
                                                                   pArraySell, pArrayBuy : Pointer) stdcall;

  THistoryTradeCallback    = procedure                                        (rAssetID  : TAssetIDRec;
                                                                                pwcDate  : PWideChar;
                                                                           nTradeNumber  : Cardinal;
                                                                           sPrice, sVol  : Double;
                                                nQtd, nBuyAgent, nSellAgent, nTradeType  : Integer) stdcall;

  TProgressCallback        = procedure                                        (rAssetID : TAssetIDRec ;
                                                                               nProgress : Integer) stdcall;


  TTinyBookCallback        = procedure                                        (rAssetID  : TAssetIDRec;
                                                                                 sPrice  : Double;
                                                                            nQtd, nSide  : Integer) stdcall;

  TAssetListCallback       = procedure                                         (rAssetID : TAssetIDRec;
                                                                                 pwcName : PWideChar) stdcall;

  TAssetListInfoCallback   = procedure                                         (rAssetID : TAssetIDRec;
                                                                 pwcName, pwcDescription : PwideChar;
                    nMinOrderQtd, nMaxOrderQtd, nLote, stSecurityType, ssSecuritySubType : Integer;
                                                 sMinPriceIncrement, sContractMultiplier : Double;
                                                                   strValidDate, strISIN : PwideChar) stdcall;

  TAssetListInfoCallbackV2 = procedure                                         (rAssetID : TAssetIDRec;
                                                                 pwcName, pwcDescription : PwideChar;
                    nMinOrderQtd, nMaxOrderQtd, nLote, stSecurityType, ssSecuritySubType : Integer;
                                                 sMinPriceIncrement, sContractMultiplier : Double;
                               strValidDate, strISIN, strSetor, strSubSetor, strSegmento : PwideChar) stdcall;

  TChangeStateTicker       = procedure                                         (rAssetID : TAssetIDRec;
                                                                                 pwcDate : PWideChar;
                                                                                  nState : Integer) stdcall;

  TAdjustHistoryCallback    = procedure                                        (rAssetID : TAssetIDRec;
                                                                                  sValue : Double;
                              strAdjustType, strObserv, dtAjuste, dtDeliber, dtPagamento : PwideChar;
                                                                            nAffectPrice : Integer) stdcall;

  TAdjustHistoryCallbackV2 = procedure                                         (rAssetID : TAssetIDRec;
                                                                                  dValue : Double;
                              strAdjustType, strObserv, dtAjuste, dtDeliber, dtPagamento : PwideChar;
                                                                                  nFlags : Cardinal;
                                                                                   dMult : Double) stdcall;

  TTheoreticalPriceCallback = procedure                                        (rAssetID : TAssetIDRec;
                                                                       sTheoreticalPrice : Double;
                                                                         nTheoreticalQtd : Int64) stdcall;

  TChangeCotation           = procedure                                      (rAssetID   : TAssetIDRec;
                                                                               pwcDate   : PWideChar;
                                                                            nTradeNumber : Cardinal;
                                                                                  sPrice : Double) stdcall;

implementation

end.
