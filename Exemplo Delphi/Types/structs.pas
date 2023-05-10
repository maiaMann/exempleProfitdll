unit structs;

interface

type
  // Asset //
  PAssetIDRec = ^TAssetIDRec;
  TAssetIDRec = packed record
    pchTicker : PWideChar;
    pchBolsa  : PWideChar;
    nFeed     : Integer;
  end;

  // Price book //
  TGroupPrice = record
      nQtd   : Integer;
      sPrice : Double;
      nCount : Integer;
  end;
  PGroupPrice = ^TGroupPrice;

  // Offer book //
  TGroupOffer = record
      nPosition  : Integer;
      nQtd       : Integer;
      nOfferID   : Int64;
      nAgent     : Integer;
      sPrice     : Double;
      strDtOffer : String;
  end;
  PGroupOffer = ^TGroupOffer;

implementation

end.
