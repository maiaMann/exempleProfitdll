# exempleProfitdll
Este repositório serve para armazenar todo o manual da dll da datasolution para o ProfitChart. Todo o conteúdo está dentro do README. Fiz isso apenas para organização pessoal por motivos específicos.

**NESTE MESMO REPOSITÓRIO HÁ OS CÓDIGOS DE EXEMPLO .PY;**

# MANUAL GERAL

ProfitDLL 64 bits - Manual de Uso
1. Descrição do Produto
Os arquivos contidos no arquivo zip estão organizados em diretórios separados para as versões de 64 bits e
32 bits. Cada diretório possui a mesma estrutura de organização de arquivos. No diretório denominado DLL e
Executável, é possível encontrar o arquivo ProfitDLL.dll para a versão de 32 bits e ProfitDLL64.dll para a versão
de 64 bits. Além disso, há um exemplo compilado em Delphi que pode ser utilizado para validar as
funcionalidades do software. Já no diretório denominado Interface, são disponibilizados arquivos contendo as
declarações das funções e tipos necessários para realizar a comunicação com a DLL em Delphi.
Existem também exemplos para 4 linguagens de programação diferentes nas pastas Exemplo.
Delphi
C#
C++
Python
Elas contém o código fonte para utilizar as principais funcionalidades do produto.
2. Descrição da Biblioteca
A biblioteca possui funções básicas de comunicação com os servidores de Roteamento e Market Data para o
desenvolvimento de aplicações 32 ou 64 bits. A DLL responde eventos dos servidores e os envia processados
em tempo real para a aplicação cliente, principalmente por meio de callbacks que serão descritos na seção
3.2.
As seções a seguir descrevem, em mais detalhes, como a comunicação entre a biblioteca e a aplicação cliente
é realizada, bem como apresentam os detalhes técnicos de cada função ou callback.
3. Interface da Biblioteca
A biblioteca expõe diversas funções chamadas diretamente pela aplicação cliente que realizam requisições
para os servidores ou diretamente para os serviços e estruturas internas da DLL. Os tipos especificados nesta
documentação estão codificados em Delphi, com exemplos específicos para outras linguagens de
programação em seus respectivos arquivos de exemplo.
Todas as estruturas necessárias para definir as funções da biblioteca são definidas a seguir:
Manual - ProfitDLL.md 3/17/2023
2 / 41
Definições:
TAssetIDRec = packed record
 pwcTicker : PWideChar; // Representa o nome do ativo ex.: "WDOFUT".
 pwcBolsa : PWideChar; // Representa a bolsa que o ativo pertence ex. (para
Bovespa): "B".
 nFeed : Integer; // Fonte dos dados 0 (Nelogica), 255 (Outro).
end;
PAssetIDRec = ^TAssetIDRec;
TAccountRec = packed record
 pwhAccountID : PWideChar; // Identificador da conta
 pwhTitular : PWideChar; // Nome do titular da conta
 pwhNomeCorretora : PWideChar; // Nome da corretora
 nCorretoraID : Integer; // Identificador da corretora
end;
PAccountRec = ^TAccountRec;
// Bolsas
gc_bvBCB = 65; // A
gc_bvBovespa = 66; // B
gc_bvCambio = 68; // D
gc_bvEconomic = 69; // E
gc_bvBMF = 70; // F
gc_bvMetrics = 75; // K
gc_bvCME = 77; // M
gc_bvNasdaq = 78; // N
gc_bvOXR = 79; // O
gc_bvPioneer = 80; // P
gc_bvDowJones = 88; // X
gc_bvNyse = 89; // Y
// Status
CONNECTION_STATE_LOGIN = 0; // Conexão com servidor de login
CONNECTION_STATE_ROTEAMENTO = 1; // Conexão com servidor de roteamento
CONNECTION_STATE_MARKET_DATA = 2; // Conexão com servidor de market data
CONNECTION_STATE_MARKET_LOGIN = 3; // Login com servidor market data
LOGIN_CONNECTED = 0; // Servidor de login conectado
LOGIN_INVALID = 1; // Login é inválido
LOGIN_INVALID_PASS = 2; // Senha inválida
LOGIN_BLOCKED_PASS = 3; // Senha bloqueada
LOGIN_EXPIRED_PASS = 4; // Senha expirada
LOGIN_UNKNOWN_ERR = 200; // Erro interno de login
ROTEAMENTO_DISCONNECTED = 0;
ROTEAMENTO_CONNECTING = 1;
ROTEAMENTO_CONNECTED = 2;
ROTEAMENTO_BROKER_DISCONNECTED = 3;
ROTEAMENTO_BROKER_CONNECTING = 4;
ROTEAMENTO_BROKER_CONNECTED = 5;
Manual - ProfitDLL.md 3/17/2023
3 / 41
MARKET_DISCONNECTED = 0; // Desconectado do servidor de market data
MARKET_CONNECTING = 1; // Conectando ao servidor de market data
MARKET_WAITING = 2; // Esperando conexão
MARKET_NOT_LOGGED = 3; // Não logado ao servidor de market data
MARKET_CONNECTED = 4; // Conectado ao market data
CONNECTION_ACTIVATE_VALID = 0; // Ativação válida
CONNECTION_ACTIVATE_INVALID = 1; // Ativação inválida
Códigos de erro:
NL_OK = 0; // Sem erros
NL_ERR_INIT = 80; // Não inicializado
NL_ERR_INVALID_ARGS = 90; // Argumento inválido
NL_ERR_INTERNAL_ERROR = 100; // Erro interno
NL_WAITING_SERVER = 110; // Esperando por dados do servidor
3.1. Funções expostas
As declarações de todas as funções expostas se encontram nesta seção. Algumas funções recebem tipos
contendo Callback no nome, estas serão descritas na próxima subseção.
function DLLInitializeLogin(
 const pwcActivationKey : PWideChar;
 const pwcUser : PWideChar;
 const pwcPassword : PWideChar;
 StateCallback : TStateCallBack;
 HistoryCallBack : THistoryCallBack;
 OrderChangeCallBack : TOrderChangeCallBack;
 AccountCallback : TAccountCallBack;
 NewTradeCallback : TNewTradeCallBack;
 NewDailyCallback : TNewDailyCallBack;
 PriceBookCallback : TPriceBookCallBack;
 OfferBookCallback : TOfferBookCallBack;
 HistoryTradeCallBack : THistoryTradeCallBack;
 ProgressCallBack : TProgressCallBack;
 TinyBookCallBack : TTinyBookCallBack) : Short; stdcall;
function DLLInitializeMarketLogin(
 const pwcActivationKey : PWideChar;
 const pwcUser : PWideChar;
 const pwcPassword : PWideChar;
 StateCallback : TStateCallBack;
 NewTradeCallback : TNewTradeCallBack;
 NewDailyCallback : TnewDailyCallBack
 PriceBookCallback : TPriceBookCallBack;
 OfferBookCallback : TOfferBookCallBack;
 HistoryTradeCallBack : THistoryTradeCallBack;
 ProgressCallBack : TProgressCallBack;
Manual - ProfitDLL.md 3/17/2023
4 / 41
 TinyBookCallBack : TTinyBookCallBack) : Short; stdcall;
function DLLFinalize: ShortInt; stdcall;
function SubscribeTicker(pwcTicker : PWideChar; pwcBolsa : PWideChar) : ShortInt;
stdcall;
function UnsubscribeTicker(pwcTicker : PWideChar; pwcBolsa : PWideChar) :
ShortInt; stdcall;
function SubscribePriceBook(pwcTicker : PWideChar; pwcBolsa : PWideChar) :
ShortInt; stdcall;
function UnsubscribePriceBook(pwcTicker : PWideChar; pwcBolsa : PWideChar) :
ShortInt; stdcall;
function SubscribeOfferBook(pwcTicker : PWideChar; pwcBolsa : PWideChar) :
ShortInt; stdcall;
function UnsubscribeOfferBook(pwcTicker : PWideChar; pwcBolsa : PWideChar) :
ShortInt; stdcall;
function GetAgentNameByID(nID : Integer) : PWideChar; stdcall;
function GetAgentShortNameByID(nID : Integer) : PWideChar; stdcall;
function GetAccount : ShortInt; stdcall;
function SendBuyOrder(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcSenha : PWideChar;
 pwcTicker : PWideChar;
 pwcBolsa : PWideChar;
 dPrice : Double;
 nAmount : Integer) : Int64; stdcall;
function SendSellOrder(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcSenha : PWideChar;
 pwcTicker : PWideChar;
 pwcBolsa : PWideChar;
 dPrice : Double;
 nAmount : Integer) : Int64; stdcall;
function SendMarketBuyOrder(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcSenha : PWideChar;
 pwcTicker : PWideChar;
 pwcBolsa : PWideChar;
 nAmount : Integer) : Int64; stdcall;
Manual - ProfitDLL.md 3/17/2023
5 / 41
function SendMarketSellOrder(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcSenha : PWideChar;
 pwcTicker : PWideChar;
 pwcBolsa : PWideChar;
 nAmount : Integer) : Int64; stdcall;
function SendStopBuyOrder(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcSenha : PWideChar;
 pwcTicker : PWideChar;
 pwcBolsa : PWideChar;
 dPrice : Double;
 dStopPrice : Double;
 nAmount : Integer) : Int64; stdcall;
function SendStopSellOrder(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcSenha : PWideChar;
 pwcTicker : PWideChar;
 pwcBolsa : PWideChar;
 dPrice : Double;
 dStopPrice : Double;
 nAmount : Integer) : Int64; stdcall;
function SendChangeOrder(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcSenha : PWideChar;
 pwcstrClOrdID : PWideChar;
 dPrice : Double;
 nAmount : Integer) : ShortInt; stdcall;
function SendCancelOrder(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcClOrdId : PWideChar;
 pwcSenha : PWideChar) : ShortInt; stdcall;
function SendCancelOrders(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcSenha : PWideChar;
 pwcTicker : PWideChar;
 pwcBolsa : PWideChar) : ShortInt; stdcall;
function SendCancelAllOrders(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcSenha : PWideChar) : ShortInt; stdcall;
Manual - ProfitDLL.md 3/17/2023
6 / 41
function SendZeroPosition(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcTicker : PWideChar;
 pwcBolsa : PWideChar;
 pwcSenha : PWideChar;
 dPrice : Double) : Int64; stdcall;
function GetOrders(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 dtStart : PWideChar;
 dtEnd : PWideChar) : ShortInt; stdcall;
function GetOrder(pwcClOrdId : PWideChar) : ShortInt; stdcall;
function GetOrderProfitID(nProfitID : Int64): ShortInt; stdcall;
function GetPosition(
 pwcIDAccount : PWideChar;
 pwcIDCorretora : PWideChar;
 pwcTicker : PWideChar;
 pwcBolsa : PWideChar) : Pointer; stdcall;
function GetHistoryTrades(
 const pwcTicker : PWideChar;
 const pwcBolsa : PWideChar;
 dtDateStart : PWideChar;
 dtDateEnd : PWideChar) : ShortInt; stdcall;
function SetServerAndPort(const strServer, strPort : PWideChar) : ShortInt;
stdcall;
function GetServerClock (var dtDate : Double; var nYear, nMonth, nDay, nHour,
nMin, nSec, nMilisec: Integer) : ShortInt; stdcall;
function SetDayTrade(bUseDayTrade : Integer): ShortInt; stdcall; forward;
function SetEnabledHistOrder(bEnabled : Integer) : ShortInt; stdcall; forward;
function SetEnabledLogToDebug(bEnabled : Integer) : ShortInt; stdcall; forward;
function RequestTickerInfo(const pwcTicker : PWideChar; const pwcBolsa :
PWideChar) : ShortInt; stdcall; forward;
function GetAllTicker(pwcBolsa : PWideChar) : ShortInt; stdcall; forward;
function SetAssetListCallback(AssetListCallback : TAssetListCallback) : ShortInt;
stdcall; forward;
function SetAssetListInfoCallback(AssetListInfoCallback : TAssetListInfoCallback)
: ShortInt; stdcall; forward;
function SetAssetListInfoCallbackV2(AssetListInfoCallbackV2 :
Manual - ProfitDLL.md 3/17/2023
7 / 41
TAssetListInfoCallbackV2) : ShortInt; stdcall; forward;
function SetChangeCotationCallback(ChangeCotation : TChangeCotation) : ShortInt;
stdcall; forward;
function SetChangeStateTickerCallback(ChangeState : TChangeStateTicker) :
ShortInt; stdcall; forward;
function SetAdjustHistoryCallback(AdjustHistory : TAdjustHistoryCallback) :
ShortInt; stdcall; forward;
function SetAdjustHistoryCallbackV2(AdjustHistory : TAdjustHistoryCallbackV2) :
ShortInt; stdcall; forward;
function SetTheoreticalPriceCallback(TheoreticalPrice : TTheoreticalPriceCallback)
: ShortInt; stdcall;
function SubscribeAdjustHistory(pwcTicker : PWideChar; pwcBolsa : PWideChar) :
ShortInt; stdcall;
function UnsubscribeAdjustHistory(pwcTicker : PWideChar; pwcBolsa : PWideChar) :
ShortInt; stdcall;
function GetLastDailyClose(const pwcTicker, pwcBolsa: var dClose : Double;
bAdjusted : Integer) : ShortInt; stdcall;
DLLInitializeLogin
Nome Tipo Descrição
const
pwcActivationKey
PWideChar Chave de ativação fornecida para login
const pwcUser PWideChar
Usuário para login da conta correspondente à
chave de ativação
const pwcPassword PWideChar Senha de login
StateCallback TStateCallBack Callback de estado da conexão
HistoryCallBack THistoryCallBack Callback de histórico de ordens
OrderChangeCallBack TOrderChangeCallBack Callback de mudança no estado de uma ordem
AccountCallback TAccountCallBack Callback de informações da conta de roteamento
NewTradeCallback TNewTradeCallBack Callback de trades em tempo real
NewDailyCallback TNewDailyCallBack Callback de dados diários agregados
PriceBookCallback TPriceBookCallBack Callback de informações do livro de preços
OfferBookCallback TOfferBookCallBack Callback de informações do livro de ofertas
Manual - ProfitDLL.md 3/17/2023
8 / 41
Nome Tipo Descrição
HistoryTradeCallBack THistoryTradeCallBack Callback de dados de histórico de trades
ProgressCallBack TProgressCallBack
Callback de progresso de alguma requisição de
histórico
TinyBookCallBack TTinyBookCallBack Callback de topo de livro
Função de inicialização dos serviços de Market Data e Roteamento da DLL. Ela irá inicializar conexão com
todos servidores e criar os serviços necessários para comunicação. Outras funções podem retornar o status de
erro NL_ERR_INIT caso DLLInitializeLogin não seja bem sucedida.
DLLInitializeMarketLogin
Nome Tipo Descrição
const
pwcActivationKey
PWideChar Chave de ativação fornecida para login
const pwcUser PWideChar
Usuário para login da conta correspondente à
chave de ativação
const pwcPassword PWideChar Senha de login
StateCallback TStateCallBack Callback de estado da conexão
NewTradeCallback TNewTradeCallBack Callback de trades em tempo real
NewDailyCallback TNewDailyCallBack Callback de dados diários agregados
PriceBookCallback TPriceBookCallBack Callback de informações do livro de preços
OfferBookCallback TOfferBookCallBack Callback de informações do livro de ofertas
HistoryTradeCallBack THistoryTradeCallBack Callback de dados de histórico de trades
ProgressCallBack TProgressCallBack
Callback de progresso de alguma requisição de
histórico
TinyBookCallBack TTinyBookCallBack Callback de topo de livro
Equivalente à função DLLInitializeLogin, porém inicializa somente serviços de Market Data.
Manual - ProfitDLL.md 3/17/2023
9 / 41
DLLFinalize
Função utilizada para finalização dos serviços da DLL.
SetServerAndPort
Nome Tipo Descrição
const strServer Double Endereço do servidor de Market Data
const strPort Integer Porta do servidor de Market Data
É usado para conectar em servidores específicos do Market Data, precisa ser chamado antes da inicialização
(DLLInitialize ou InitializeMarket).
Importante: apenas utilizar essa função com orientação da equipe de desenvolvimento, a DLL funciona da
melhor maneira escolhendo os servidores internamente
GetServerClock
Nome Tipo Descrição
var dtDate Double Data codificada como Double
var nYear Integer Ano
var nMonth Integer Mês
var nDay Integer Dia
var nHour Integer Hora
var nMin Integer Minuto
var nSec Integer Segundo
var nMilisec Integer Milissegundo
Retorna o horário do servidor de Market Data, pode ser chamado somente após inicialização. O parâmetro
dtDate corresponde a uma referência para Double que segue o padrão TDateTime do Delphi, descrito em
http://docwiki.embarcadero.com/Libraries/Sydney/en/System.TDateTime. Os outros parâmetros também são
passados por referência ao caller e somente representam os valores de data calendário do valor codificado no
parâmetro dtDate.
GetLastDailyClose
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
Manual - ProfitDLL.md 3/17/2023
10 / 41
Nome Tipo Descrição
const pwcBolsa PWideChar Bolsa do ativo
var dClose Double Valor retornado de fechamento da última sessão
bAdjusted Integer Indica se deve ajustar o preço
A função retorna o valor do fechamento (dClose) do candle anterior ao dia atual, de acordo com o parâmetro
bAdjusted. Se bAdjusted for 0, o valor não ajustado é retornado; caso contrário, o valor ajustado é retornado.
Para que a função retorne NL_OK com dados, é necessário que SubscribeTicker tenha sido previamente
chamada para o mesmo ativo. Na primeira chamada da função, os dados são requisitados ao servidor e a
função retorna NL_WAITING_SERVER. Todas as chamadas subsequentes para o mesmo ativo retornam os
dados já carregados. Ativos inválidos retornam NL_ERR_INVALID_ARGS. Se os dados da série diária ou ajustes
não estiverem previamente carregados, essa chamada irá carregá-los e, consequentemente, disparar os
callbacks progressCallback e adjustHistoryCallback.
SubscribeTicker
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
const pwcBolsa PWideChar Bolsa do ativo
É usado para receber as cotações em tempo real de determinado ativo. As informações são recebidas
posteriormente à inscrição assim que disponíveis pelo callback especificado no parâmetro
NewTradeCallback da função de inicialização. UnsubscribeTicker desativa este serviço.
UnsubscribeTicker
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
const pwcBolsa PWideChar Bolsa do ativo
Solicita ao serviço de Market Data que interrompa o envio de cotações em tempo real de um determinado
ativo.
SubscribeOfferBook
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
const pwcBolsa PWideChar Bolsa do ativo
Manual - ProfitDLL.md 3/17/2023
11 / 41
É usado para receber informações do livro de ofertas em tempo real. As informações são recebidas
posteriormente à inscrição assim que disponíveis pelo callback especificado no parâmetro
OfferBookCallback da função de inicialização. UnsubscribeOfferBook desativa esse serviço.
UnsubscribeOfferBook
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
const pwcBolsa PWideChar Bolsa do ativo
Solicita ao serviço de Market Data que interrompa o envio em tempo real do livro de ofertas de um
determinado ativo.
SubscribePriceBook
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
const pwcBolsa PWideChar Bolsa do ativo
É usado para receber informações do livro de preços em tempo real. As informações são recebidas
posteriormente à inscrição assim que disponíveis pelo callback especificado no parâmetro
PriceBookCallback da função de inicialização. UnsubscribePriceBook desativa esse serviço.
UnsubscribePriceBook
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
const pwcBolsa PWideChar Bolsa do ativo
Solicita ao serviço de Market Data que interrompa o envio do livro de preços em tempo real de um
determinado ativo.
As chamadas de Subscribe e Unsubscribe SubscribeTicker, UnsubscribeTicker, SubscribePriceBook,
UnsubscribePriceBook, SubscribeOfferBook, UnsubscribeOfferBook recebe os seus parâmetros no
seguinte padrão:
Ticker: PETR4, Bolsa: B
Ticker: WINFUT, Bolsa: F
Mais exemplos de bolsas podem ser encontradas na seção de declarações.
Manual - ProfitDLL.md 3/17/2023
12 / 41
SubscribeAdjustHistory
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
const pwcBolsa PWideChar Bolsa do ativo
É utilizado para receber histórico de ajustes do ativo determinado ticker. É necessário fornecer a função de
callback SetAdjustHistoryCallback ou SetAdjustHistoryCallbackV2 para utilizar esse subscribe.
UnsubscribeAdjustHistory
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
const pwcBolsa PWideChar Bolsa do ativo
Solicita ao serviço de Market Data que interrompa o envio de informações de ajustes de um determinado
ativo.
GetAgentNameByID e GetAgentShortNameByID
Nome Tipo Descrição
nID Integer Identificador do agente negociante
O valor retornado apresenta o nome completo e abreviado, respectivamente, deste agente.
GetHistoryTrades
Nome Tipo Descrição
const
pwcTicker
PWideChar Ticker do ativo
const
pwcBolsa
PWideChar Bolsa do ativo
dtDateStart PWideChar
Data de início da requisição no formato DD/MM/YYYY HH:mm:SS
(mm minuto MM mês)
dtDateEnd PWideChar
Data do fim da requisição no formato DD/MM/YYYY HH:mm:SS (mm
minuto MM mês)
É utilizado para solicitar as informações do histórico de um ativo a partir de uma data (pwcTicker = ‘PETR4’;
dtDateStart = ‘06/08/2018 09:00:00’; dtDateEnd= ‘06/08/2018 18:00:00’). Retorno será dado na função de
callback THistoryTradeCallBack especificada por parâmetro para a função de inicialização. Em
Manual - ProfitDLL.md 3/17/2023
13 / 41
TProgressCallBack será retornado o progresso de Download (1 até 100), o progresso igual a 1000 indica
que todos trades foram enviadas para a aplicação cliente.
SetDayTrade
Nome Tipo Descrição
bUseDayTrade Integer Indica se deve usar a flag de day trade (1 true, 0 false)
Função disponível para clientes cujas corretoras tenham controle de risco DayTrade. Desta forma, as ordens
são enviadas com a tag DayTrade. O parâmetro é um boleano (0 = False, 1 = True). Ao definí-lo como true,
todas ordens serão enviadas com o modo DayTrade ativado. Para desativar, basta setar para falso.
SetEnabledLogToDebug
Nome Tipo Descrição
bEnabled Integer Indica se deve salvar logs de debug
Função para definir uma se a DLL deve salvar logs para debug (1 = salvar / 0 = Não salvar).
RequestTickerInfo
Nome Tipo Descrição
const pwcTicker PWideChar Ticker do ativo
const pwcBolsa PWideChar Bolsa do ativo
É utilizado para buscar novas informações do ativo (ex. ISIN). A resposta é retornada nos callbacks
TAssetListInfoCallback, TAssetListInfoCallbackV2 e TAssetListCallback, caso os mesmos tenham
sido enviados à DLL por meio das funções SetAssetListInfoCallback, SetAssetListInfoCallbackV2 e
SetAssetListCallback.
GetAllTicker
É utilizado para solicitação de informações de ativos de uma bolsa (B=Bovespa, F=BMF, ''=TODAS).
As funções abaixo fornecem um endereço de callback para a DLL retornar informações. Elas são opcionais
para utilização da biblioteca. Caso elas não sejam especificadas, as informações correspondentes não serão
fornecidas ao serem requisitadas.
SetChangeCotationCallback
Manual - ProfitDLL.md 3/17/2023
14 / 41
Utilizado para definir uma função de callback do tipo TChangeCotation, esta função notifica sempre que o
ativo sofrer modificação no preço.
SetAssetListCallback
Utilizado para definir uma função de callback do tipo TAssetListCallback, responsável pelo retorno da
informações de ativos.
SetAssetListInfoCallback
Utilizado para definir uma função de callback do tipo TAssetListInfoCallback, responsável pelo retorno da
informações de ativos, retorna informações adicionais comparada a AssetListCallback.
SetAssetListInfoCallbackV2
Semelhante a SetAssetListInfoCallback, porém retorna informações de setor, subsetor e segmento.
SetChangeStateTickerCallback
Utilizado para definir o callback TChangeStateTicker que informa as modificações do estado do ticker, tais
como, se o ativo está em leilão, suspenso, em pré-fechamento, after market ou fechado.
SetAdjustHistoryCallback
Utilizado para definir o callback TAdjustHistoryCallback que informa o histórico de ajustes do ticker.
SetAdjustHistoryCallbackV2
Utilizado para definir o callback TAdjustHistoryCallbackV2 que informa o histórico de ajustes do ticker.
SetTheoreticalPriceCallback
Utilizado para definir a função de callback do tipo TTheoreticalPriceCallback, que recebe o preço e
quantidades teóricas durante o leilão.
As funções descritas abaixo estão disponíveis somente para inicialização com roteamento, após a utilização
da função DLLInitializeLogin na inicialização.
GetAccount
Manual - ProfitDLL.md 3/17/2023
15 / 41
Função que retorna informações das contas vinculadas através do callback TAccountCallback passado como
parâmetro para a função de inicialização.
SendBuyOrder
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcSenha PWideChar Senha de roteamento
pwcTicker PWideChar Ticker do ativo a ser negociado
pwcBolsa PWideChar Bolsa do ativo a ser negociado
dPrice Double Preço alvo
nAmount Integer Quantidade a ser negociada
Envia ordem de compra limite. Retorna o ID interno (por sessão) da ordem que pode ser comparado com o
retorno do THistoryCallBack.
SendSellOrder
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcSenha PWideChar Senha de roteamento
pwcTicker PWideChar Ticker do ativo a ser negociado
pwcBolsa PWideChar Bolsa do ativo a ser negociado
dPrice Double Preço alvo
nAmount Integer Quantidade a ser negociada
Envia ordem de venda limite. Retorna o ID interno (por sessão) da ordem que pode ser comparado com o
retorno do THistoryCallBack.
SendMarketBuyOrder
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
Manual - ProfitDLL.md 3/17/2023
16 / 41
Nome Tipo Descrição
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcSenha PWideChar Senha de roteamento
pwcTicker PWideChar Ticker do ativo a ser negociado
pwcBolsa PWideChar Bolsa do ativo a ser negociado
nAmount Integer Quantidade a ser negociada
Envia ordem de compra a mercado. Retorna o ID interno (por sessão) da ordem que pode ser comparado
com o retorno do THistoryCallBack.
SendMarketSellOrder
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcSenha PWideChar Senha de roteamento
pwcTicker PWideChar Ticker do ativo a ser negociado
pwcBolsa PWideChar Bolsa do ativo a ser negociado
nAmount Integer Quantidade a ser negociada
Envia ordem de venda a mercado. Retorna o ID interno (por sessão) da ordem que pode ser comparado com
o retorno do THistoryCallBack.
SendStopBuyOrder
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcSenha PWideChar Senha de roteamento
pwcTicker PWideChar Ticker do ativo a ser negociado
pwcBolsa PWideChar Bolsa do ativo a ser negociado
dPrice Double Preço alvo de compra
dStopPrice Double Preço de stop
nAmount Integer Quantidade a ser negociada
Manual - ProfitDLL.md 3/17/2023
17 / 41
Envia ordem de compra stop. Retorna o ID interno (por sessão) da ordem que pode ser comparado com o
retorno do THistoryCallBack.
SendStopSellOrder
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcSenha PWideChar Senha de roteamento
pwcTicker PWideChar Ticker do ativo a ser negociado
pwcBolsa PWideChar Bolsa do ativo a ser negociado
dPrice Double Preço alvo de venda
dStopPrice Double Preço de stop
nAmount Integer Quantidade a ser negociada
Envia ordem de venda stop. Retorna o ID interno (por sessão) da ordem que pode ser comparado com o
retorno do THistoryCallBack.
SendChangeOrder
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcSenha PWideChar Senha de roteamento
pwcstrClOrdID PWideChar
ClOrdID da ordem a ser modificada (Fornecido em
OrderChangeCallBack)
dPrice PWideChar Preço alvo após edição
nAmount Integer Quantidade após edição
Envia uma ordem de modificação. Quando a modificação for de uma ordem stop, o preço stop deve ser
informado como preço alvo e o preço limite será calculado com base no mesmo offset.
SendCancelOrder
Nome Tipo Descrição
Manual - ProfitDLL.md 3/17/2023
18 / 41
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcClOrdId PWideChar
ClOrdID da ordem a ser cancelada (Fornecido em
OrderChangeCallBack)
pwcSenha PWideChar Senha de roteamento
Envia uma ordem de cancelamento. O resultado da requisição de cancelamento pode ser acompanhado em
TOrderChangeCallback.
SendCancelOrders
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcSenha PWideChar Senha de roteamento
pwcTicker PWideChar Ticker do ativo a ser negociado
pwcBolsa PWideChar Bolsa do ativo a ser negociado
Envia uma ordem para cancelar todas ordens de um ativo. O resultado da requisição de cancelamento pode
ser acompanhado em TOrderChangeCallback para cada ordem cancelada.
SendCancelAllOrders
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcSenha PWideChar Senha de roteamento
Envia uma ordem para cancelar todas ordens em aberto de todos ativos. O resultado da requisição de
cancelamento pode ser acompanhado em TOrderChangeCallback para cada ordem cancelada.
SendZeroPosition
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
Manual - ProfitDLL.md 3/17/2023
19 / 41
Nome Tipo Descrição
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
pwcTicker PWideChar Ticker do ativo a ser negociado
pwcBolsa PWideChar Bolsa do ativo a ser negociado
pwcSenha PWideChar Senha de roteamento
dPrice Double Preço da ordem
Envia uma ordem para zerar a posição de um determinado ativo. Retorna o ID interno (por sessão) da ordem
de zeragem que pode ser comparado com o retorno do THistoryCallBack.
GetOrders
Nome Tipo Descrição
pwcIDAccount PWideChar Identificador de conta (fornecido em GetAccount)
pwcIDCorretora PWideChar Identificador da corretora (fornecido em GetAccount)
dtStart PWideChar Data inicial no formato DD/MM/YYYY
dtEnd PWideChar Data final no formato DD/MM/YYYY
Função que retorna as ordens em determinado período. Retorno feito pelo callback THistoryCallBack,
passado como parâmetro para a função de inicialização.
GetOrder
Nome Tipo Descrição
pwcClOrdId PWideChar ClOrdID da ordem a ser retornada
Função que retorna dados de uma ordem a partir de um ClOrdID. Retorno feito pelo callback
TOrderChangeCallback, passado como parâmetro para a função de inicialização.
GetOrderProfitID
Nome Tipo Descrição
nProfitID Int64 ProfitID da ordem a ser retornada
Função que retorna dados de uma ordem a partir de um ProfitID (ID interno por sessão). Retorno feito pelo
callback TOrderChangeCallback, passado como parâmetro para a função de inicialização. O ProfitID é válido
apenas durante a execução da aplicação, ao contrário do ClOrdID. Esse ID é o retorno das funções de envio
de ordem.
Manual - ProfitDLL.md 3/17/2023
20 / 41
GetPosition
Função que retorna a posição para determinado ticker. Retorna uma estrutura de dados especificada abaixo.
Com tamanho total (Total 90 + N + T + K):
Campo Tipo Tamanho
Quantidade de contas Integer 4 bytes
Tamanho do buffer Integer 4 bytes
ID da corretora Integer 4 bytes
N tamanho string Conta Short 2 bytes
String conta (Array de caracteres) N Bytes
T tamanho string Titular Short 2 bytes
String titular (Array de caracteres) T Bytes
K tamanho string Ticker Short 2 bytes
String ticker (Array de caracteres) K Bytes
Intraday nQtd Integer 4 bytes
Intraday dPrice Double 8 bytes
Day SellAvgPriceToday Double 8 bytes
Day SellQtdToday Integer 4 bytes
Day BuyAvgPriceToday Double 8 bytes
Day BuyQtdToday Integer 4 bytes
Custodia Quantidade em D+1 Integer 4 bytes
Custodia Quantidade em D+2 Integer 4 bytes
Custodia Quantidade em D+3 Integer 4 bytes
Custodia Quantidade bloqueada Integer 4 bytes
Custodia Quantidade Pending Integer 4 bytes
Custodia Quantidade alocada Integer 4 bytes
Custodia Quantidade provisionada Integer 4 bytes
Custodia Quantidade da posição Integer 4 bytes
Custodia Quantidade Disponível Integer 4 bytes
SetEnabledHistOrder
Manual - ProfitDLL.md 3/17/2023
21 / 41
Esta função é utilizada para desativar/ativar o histórico e o update automático de ordens ao iniciar a aplicação
(1 = Ativar / 0 = Desativar). Quando o histórico é desativado, a aplicação não recebe automaticamente os
dados de ordens no início e, por isso, chamadas como GetPosition, que exigem a montagem da posição
utilizando as operações, não retornarão resultados válidos. Para desativar o update automático, esta função
deve ser utilizada logo após a chamada das funções de inicialização. É importante ressaltar que, ao desativar o
histórico, o controle de posição não será calculado corretamente pela plataforma e as funcionalidades de
zeragem e status da ordem podem ser comprometidas. O usuário deve estar ciente desses riscos antes de
desativar o histórico..
3.2 Callbacks
Essa seção descreve como devem ser declaradas e o objetivo de cada função de callback da biblioteca.
Importante: Outras funções da DLL não devem ser utilizadas dentro de um callback.
Callbacks são chamados a partir da thread ConnectorThread e portanto estão em uma thread diferente da
thread principal do programa do cliente.
As funções de callbacks devem ser todas declaradas com a convenção de chamadas stdcall
(https://en.wikipedia.org/wiki/X86_calling_conventions). Isso é válido para ambas versões, 32 e 64 bits.
TStateCallBack = procedure(nConnStateType : Integer; nResult : Integer) stdcall;
TProgressCallBack = procedure (rAssetID : TAssetIDRec; nProgress : Integer)
stdcall;
TNewTradeCallback = procedure(
 rAssetID : TAssetIDRec;
 pwcDate : PWideChar;
 nTradeNumber : Cardinal;
 dPrice : Double;
 dVol : Double;
 nQtd : Integer;
 nBuyAgent : Integer;
 nSellAgent : Integer;
 nTradeType : Integer;
 bEdit : Char) stdcall;
TNewDailyCallback = procedure(
 rAssetID : TAssetIDRec;
 pwcDate : PWideChar;
 dOpen : Double;
 dHigh : Double;
 dLow : Double;
 dClose : Double;
 dVol : Double;
 dAjuste : Double;
 dMaxLimit : Double;
 dMinLimit : Double;
 dVolBuyer : Double;
Manual - ProfitDLL.md 3/17/2023
22 / 41
 dVolSeller : Double;
 nQtd : Integer;
 nNegocios : Integer;
 nContratosOpen : Integer;
 nQtdBuyer : Integer;
 nQtdSeller : Integer;
 nNegBuyer : Integer;
 nNegSeller : Integer) stdcall;
TPriceBookCallback = procedure(
 rAssetID : TAssetIDRec;
 nAction : Integer;
 nPosition : Integer;
 nSide : Integer;
 nQtds : Integer;
 nCount : Integer;
 dPrice : Double;
 pArraySell : Pointer;
 pArrayBuy : Pointer) stdcall;
TOfferBookCallback = procedure(
 rAssetID : TAssetIDRec ;
 nAction : Integer;
 nPosition : Integer;
 Side : Integer;
 nQtd : Integer;
 nAgent : Integer;
 nOfferID : Int64;
 dPrice : Double;
 bHasPrice : Char;
 bHasQtd : Char;
 bHasDate : Char;
 bHasOfferID : Char;
 bHasAgent : Char;
 pwcDate : PWideChar;
 pArraySell : Pointer
 pArrayBuy : Pointer) stdcall;
TAccountCallback = procedure (
 nCorretora : Integer;
 CorretoraNomeCompleto : PWideChar;
 AccountID : PWideChar
 NomeTitular : PWideChar) stdcall; forward;
TOrderChangeCallBack = procedure (
 rAssetID : TAssetIDRec;
 nCorretora : Integer;
 nQtd : Integer;
 nTradedQtd : Integer;
 nLeavesQtd : Integer;
 nSide : Integer;
 dPrice : Double;
 dStopPrice : Double;
 dAvgPrice : Double;
Manual - ProfitDLL.md 3/17/2023
23 / 41
 nProfitID : Int64;
 TipoOrdem : PWideChar;
 Conta : PWideChar;
 Titular : PWideChar;
 ClOrdID : PWideChar;
 Status : PWideChar;
 Date : PWideChar;
 TextMessage : PWideChar) stdcall
;
THistoryCallBack = procedure
(
 rAssetID : TAssetIDRec;
 nCorretora : Integer;
 nQtd : Integer;
 nTradedQtd : Integer;
 nLeavesQtd : Integer;
 nSide : Integer;
 dPrice : Double;
 dStopPrice : Double;
 dAvgPrice : Double;
 nProfitID : Int64;
 TipoOrdem : PWideChar;
 Conta : PWideChar;
 Titular : PWideChar;
 ClOrdID : PWideChar;
 Status : PWideChar;
 Date : PWideChar) stdcall
;
THistoryTradeCallBack = procedure
(
 rAssetID : TAssetIDRec;
 pwcDate : PWideChar;
 nTradeNumber : Cardinal;
 dPrice : Double;
 dVol : Double;
 nQtd : Integer;
 nBuyAgent : Integer;
 nSellAgent : Integer;
 nTradeType : Integer) stdcall
;
TTinyBookCallBack = procedure
(
 rAssetID : TAssetIDRec;
 dPrice : Double;
 nQtd : Integer;
 nSide : Integer) stdcall
;
TAssetListCallback = procedure
(
 rAssetID : TAssetIDRec;
 pwcName : PWideChar) stdcall
;
TAssetListInfoCallback = procedure
(
 rAssetID : TAssetIDRec;
 pwcName : PWideChar;
 pwcDescription : PWideChar;
 nMinOrderQtd : Integer;
 nMaxOrderQtd : Integer;
Manual - ProfitDLL.md 3/17/2023
24 / 41
 nLote : Integer;
 stSecurityType : Integer;
 ssSecuritySubType : Integer;
 dMinPriceIncrement : Double;
 dContractMultiplier : Double;
 strValidDate : PWideChar;
 strISIN : PWideChar) stdcall;
TAssetListInfoCallbackV2 = procedure(
 rAssetID : TAssetIDRec;
 pwcName : PWideChar;
 pwcDescription : PWideChar;
 nMinOrderQtd : Integer;
 nMaxOrderQtd : Integer;
 nLote : Integer;
 stSecurityType : Integer;
 ssSecuritySubType : Integer;
 dMinPriceIncrement : Double;
 dContractMultiplier : Double;
 strValidDate : PWideChar;
 strISIN : PWideChar;
 strSetor : PWideChar;
 strSubSetor : PWideChar;
 strSegmento : PWideChar) stdcall;
TChangeStateTicker = procedure(
 rAssetID : TAssetIDRec;
 pwcDate : PWideChar;
 nState : Integer) stdcall;
TAdjustHistoryCallback = procedure(
 rAssetID : TAssetIDRec;
 dValue : Double;
 strAdjustType : PWideChar;
 strObserv : PWideChar;
 dtAjuste : PWideChar;
 dtDeliber : PWideChar;
 dtPagamento : PWideChar;
 nAffectPrice : Integer) stdcall;
TAdjustHistoryCallbackV2 = procedure(
 rAssetID : TAssetIDRec;
 dValue : Double;
 strAdjustType : PwideChar;
 strObserv : PwideChar;
 dtAjuste : PwideChar;
 dtDeliber : PwideChar;
 dtPagamento : PwideChar;
 nFlags : Cardinal;
 dMult : Double) stdcall;
TTheoreticalPriceCallback = procedure (
 rAssetID : TAssetIDRec;
 dTheoreticalPrice : Double;
Manual - ProfitDLL.md 3/17/2023
25 / 41
 nTheoreticalQtd : Int64) stdcall;
TChangeCotation = procedure(
 rAssetID : TAssetIDRec;
 pwcDate : PWideChar;
 nTradeNumber : Cardinal;
 dPrice : Double) stdcall;
TStateCallBack
Corresponde ao Callback para informar o estado de login, de conexão, de roteamento e de ativação do
produto. De acordo com o tipo de nConnStateType informado, sendo eles:
CONNECTION_STATE_LOGIN = 0; // Conexão com servidor de login
CONNECTION_STATE_ROTEAMENTO = 1; // Conexão com servidor de roteamento
CONNECTION_STATE_MARKET_DATA = 2; // Conexão com servidor de market data
CONNECTION_STATE_MARKET_LOGIN = 3; // Login com servidor market data
LOGIN_CONNECTED = 0; // Servidor de login conectado
LOGIN_INVALID = 1; // Login é inválido
LOGIN_INVALID_PASS = 2; // Senha inválida
LOGIN_BLOCKED_PASS = 3; // Senha bloqueada
LOGIN_EXPIRED_PASS = 4; // Senha expirada
LOGIN_UNKNOWN_ERR = 200; // Erro interno de login
ROTEAMENTO_DISCONNECTED = 0;
ROTEAMENTO_CONNECTING = 1;
ROTEAMENTO_CONNECTED = 2;
ROTEAMENTO_BROKER_DISCONNECTED = 3;
ROTEAMENTO_BROKER_CONNECTING = 4;
ROTEAMENTO_BROKER_CONNECTED = 5;
MARKET_DISCONNECTED = 0; // Desconectado do servidor de market data
MARKET_CONNECTING = 1; // Conectando ao servidor de market data
MARKET_WAITING = 2; // Esperando conexão
MARKET_NOT_LOGGED = 3; // Não logado ao servidor de market data
MARKET_CONNECTED = 4; // Conectado ao market data
CONNECTION_ACTIVATE_VALID = 0; // Ativação válida
CONNECTION_ACTIVATE_INVALID = 1; // Ativação inválida
Sendo o tipo nConnStateType recebido um dos valores de CONNECTION_STATE, e nResult o estado de login
do serviço específico. Os valores corretos para uma conexão válida são:
nConnStateType = CONNECTION_STATE_LOGIN
nResult = LOGIN_CONNECTED
nConnStateType = CONNECTION_STATE_ROTEAMENTO
nResult = ROTEAMENTO_CONNECTED
nConnStateType = CONNECTION_STATE_MARKET_DATA
Manual - ProfitDLL.md 3/17/2023
26 / 41
nResult = MARKET_CONNECTED
nConnStateType = CONNECTION_STATE_MARKET_LOGIN
nResult = CONNECTION_ACTIVATE_VALID
TNewTradeCallback
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual o trade pertence
pwcDate PWideChar
Data do trade no formato DD/MM/YYYY HH:mm:SS.ZZZ (mm
minuto, MM mês e ZZZ milissegundo)
nTradeNumber Cardinal Número de série de um trade
dPrice Double Preço de execução
dVol Double Volume financeiro
nQtd Integer Quantidade
nBuyAgent Integer Agente comprador
nSellAgent Integer Agente vendedor
nTradeType Integer Tipo do trade
bEdit Char Indica se é uma edição
Corresponde ao Callback para informar um novo trade, recebido após se inscrever para este mesmo ativo
(segundo função SubscribeTicker já especificada). O nTradeNumber é o identificador único do trade por
pregão. bEdit informa se o trade recebido é uma edição (informação da bolsa) ou uma adição. O ID para
identificar um trade editado é o pwcDate. tradeType indica o tipo de trade segundo a tabela abaixo:
1. Cross trade
2. Compra agressão
3. Venda agressão
4. Leilão
5. Surveillance
6. Expit
7. Options Exercise
8. Over the counter
9. Derivative Term
10. Index
11. BTC
12. On Behalf
13. RLP
32. Desconhecido
TNewDailyCallback
Nome Tipo Descrição
Manual - ProfitDLL.md 3/17/2023
27 / 41
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual o trade pertence
pwcDate PWideChar
Data do trade no formato DD/MM/YYYY HH:mm:SS.ZZZ (mm
minuto, MM mês e ZZZ milissegundo)
dOpen Double Preço do trade na abertura do mercado
dHigh Double Maior preço atingido
dLow Double Menor preço atingido
dClose Double Preço do último trade ocorrido
dVol Double Volume financeiro
dAjuste Double Ajuste do preço
dMaxLimit Double Limite superior de preço para ordem
dMinLimit Double Limite inferior de preço para ordem
dVolBuyer Double Volume de compradores
dVolSeller Double Volume de vendedores
nQtd Integer Quantidade
nNegocios Integer Número total de negócios ocorridos
nContratosOpen Integer Número de contratos abertos
nQtdBuyer Integer Número de compradores
nQtdSeller Integer Número de vendedores
nNegBuyer Integer Número de negócios compradores
nNegSeller Integer Número de negócios vendedores
Corresponde ao callback para informar uma nova cotação com informações agregadas do dia de pregão.
TPriceBookCallback
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual o livro pertence
nAction Integer Ação a ser feita no livro
nPosition Integer Posição a ser inserida a oferta
nSide Integer Compra ou venda (Compra=0, Venda=1)
nQtds Integer Quantidade vendida/comprada
nCount Integer Quantidade de oferta vendida/comprada
Manual - ProfitDLL.md 3/17/2023
28 / 41
Nome Tipo Descrição
dPrice Double Preço ofertado
pArraySell Pointer Livro completo de venda
pArrayBuy Pointer Livro completo de compra
Corresponde ao Callback para informar uma atualização no livro de preços. Os parâmetros são válidos ou não
de acordo com o valor de nAction, descrito abaixo discriminadamente:
rAssetID: Ticker;
nAction: (atAdd = 0, atEdit = 1, atDelete = 2, atDeleteFrom = 3, atFullBook = 4);
nPosition: Posição no grid; (Válido em atAdd, atEdit, atDelete e atDeleteFrom).
Side: Compra ou venda; (Sempre válido).
nQtds: Quantidade vendida/Comprada; (Válido em atAdd e atEdit).
nCount: Quantidade de oferta Vendida/Comprada; (Válido em atAdd e atEdit).
dPrice: Preço; (Válido em atAdd).
pArraySell, pArrayBuy: Lista com as ofertas de compra/venda; (Válidos em atFullBook).
Esse callback foi feito de modo a manter uma lista de ofertas de venda e compra separadas. Portanto, cada
nAction recebido deve ser tratado de forma a alterar essas listas, dependendo do lado recebido em nSide,
como descrito a seguir. Todos os ajustes que dependem de nPosition se referem à posição a partir do final da
lista (em listas com início em 0, size - nPosition - 1).
atAdd: Inserir uma nova oferta após posição dada por nPosition.
atDelete: Deletar uma oferta na posição dada por nPosition.
atDeleteFrom: Remover todas as ofertas a partir da posição dada por nPosition.
atEdit: Atualizar as informações da oferta que se encontra na posição dada por nPosition.
atFullBook: Criação do book com todas as ofertas existentes.
Essas informações são recebidas através dos parâmetros pArrayBuy e pArraySell. Para criação da lista, ao
receber atFullBook, ambos arrays pArrayBuy e pArraySell possuem o seguinte layout em memória:
Cabeçalho
Campo Tipo Tamanho Offset
Quantidade de ofertas (Q) Integer 4 bytes 0
Tamanho do array (deve ser usado em FreePointer) Integer 4 bytes 4
Q entradas a serem inseridas no livro, contendo
Campo Tipo Tamanho Offset
Preço Double 8 bytes 8
Quantidade Integer 4 bytes 16
Count Integer 4 bytes 20
Manual - ProfitDLL.md 3/17/2023
29 / 41
Para mais detalhes de como montar o livro corretamente, consultar exemplos em C++ e Delphi.
TOfferBookCallback
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual o livro pertence
nAction Integer Ação a ser feita no livro
nPosition Integer Posição a ser inserida a oferta
nSide Integer Compra ou venda (Compra=0, Venda=1)
nQtd Integer Quantidade vendida/comprada
nAgent Integer Identificador do agente
nOfferID Integer Identificador da oferta
dPrice Double Preço ofertado
bHasPrice Char 1 byte para especificar se existe preço
bHasQtd Char 1 byte para especificar se existe quantidade
bHasDate Char 1 byte para especificar se existe data
bHasOfferID Char 1 byte para especificar se existe id de oferta
bHasAgent Char 1 byte para especificar se existe agente
pwcDate PWideChar
Data da oferta no formato DD/MM/YYYY HH:mm:SS.ZZZ (mm
minuto, MM mês e ZZZ milissegundo)
pArraySell Pointer Livro completo de venda
pArrayBuy Pointer Livro completo de compra
Corresponde ao Callback para informar uma atualização no livro de ofertas:
rAssetID: Ticker; nAction: (atAdd = 0, atEdit = 1, atDelete = 2, atDeleteFrom = 3, atFullBook = 4);
nPosition: Posição no array; nSide: Lado da ordem (Compra=0, Venda=1);
nQtd: Quantidade vendida/Comprada;
nAgent: indicam os IDs dos agentes de compra e venda, respectivamente; Pode-se se obter o nome
destes através das funções GetAgentNameByID e GetAgentShortNameByID já especificadas;
O callback é tratado seguindo a mesma especificação do TPriceBookCallback, com exceção do layout dos
arrays pArrayBuy e pArraySell:
Cabeçalho
Campo Tipo Tamanho Offset
Quantidade de ofertas (Q) Integer 4 bytes 0
Tamanho do array (deve ser usado em FreePointer) Integer 4 bytes 4
Manual - ProfitDLL.md 3/17/2023
30 / 41
Q entradas a serem inseridas no livro, contendo
Campo Tipo Tamanho Offset
Preço Double 8 bytes 8
Quantidade Integer 4 bytes 16
Agente Integer 4 bytes 20
OfferID Int64 8 bytes 24
T tamanho string Data Short 2 bytes 32
Data da oferta Array of bytes T bytes 34
THistoryTradeCallBack
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual o trade pertence
pwcDate PWideChar
Data do trade no formato DD/MM/YYYY HH:mm:SS.ZZZ (mm
minuto, MM mês e ZZZ milissegundo)
nTradeNumber Cardinal Número de série de um trade
dPrice Double Preço de execução
dVol Double Volume financeiro
nQtd Integer Quantidade
nBuyAgent Integer Agente comprador
nSellAgent Integer Agente vendedor
nTradeType Integer Tipo do trade
Corresponde ao Callback de trades que foram solicitados a partir da função GetHistoryTrades.
TProgressCallBack
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual o pedido de histórico se refere
nProgress Integer Valor de progresso (0-100 e 1000)
Corresponde ao Callback do progresso do THistoryTradeCallBack. Quando o progresso for igual a 1000
significa que todos trades foram enviadas para a aplicação cliente.
TTinyBookCallBack
Nome Tipo Descrição
Manual - ProfitDLL.md 3/17/2023
31 / 41
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual a oferta pertence
dPrice Double Preço da oferta
nQtd Integer Quantidade
nSide Integer Lado comprador ou vendedor (Compra=0, Venda=1)
Corresponde ao Callback do topo do livro de preço. rAssetID informa a qual ativo pertence de acordo com a
estrutura TAssetIDRec já especificada. sPrice: Preço; nQtd : Quantidade venda/compra; nSide: Lado da ordem
(Compra=0, Venda=1)
Abaixo estão descritas os callbacks apenas disponíveis após a inicialização utilizando a função
DLLInitializeLogin, portanto somente para inicialização com roteamento.
TAccountCallback
Nome Tipo Descrição
nCorretora Integer Identificador da corretora
CorretoraNomeCompleto PWideChar Nome completo da corretora
AccountID PWideChar Identificação da conta de cliente
NomeTitular PWideChar Nome do titular da conta
Corresponde ao Callback para informar as contas existentes. É possível verificar se a conta é de simulação
através do nome ou identificador da corretora.
TOrderChangeCallBack
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual o livro pertence
nCorretora Integer Identificador da corretora
nQtd Integer Quantidade da ordem
nTradedQtd Integer Quantidade já executada
nLeavesQtd Integer Quantidade pendente de execução
nSide Integer Lado da ordem (Compra=1, Venda=2)
dPrice Double Preço da ordem
dStopPrice Double Preço de stop em caso de ordem stop
dAvgPrice Double Média do preço executado
nProfitID Int64 Identificador interno por sessão da ordem
Manual - ProfitDLL.md 3/17/2023
32 / 41
Nome Tipo Descrição
TipoOrdem PWideChar Tipo da ordem
Conta PWideChar Identificador da conta
Titular PWideChar Titular da conta
ClOrdID PWideChar Identificador único da ordem (permanente)
Status PWideChar Status da ordem
Date PWideChar Data de execução da ordem
TextMessage PWideChar Mensagem de informações extras
Corresponde ao Callback para informar as modificações de ordens enviadas por uma conta.
THistoryCallBack
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual o livro pertence
nCorretora Integer Identificador da corretora
nQtd Integer Quantidade da ordem
nTradedQtd Integer Quantidade já executada
nLeavesQtd Integer Quantidade pendente de execução
nSide Integer Lado da ordem (Compra=1, Venda=2)
dPrice Double Preço da ordem
dStopPrice Double Preço de stop em caso de ordem stop
dAvgPrice Double Média do preço executado
nProfitID Int64 Identificador interno por sessão da ordem
TipoOrdem PWideChar Tipo da ordem
Conta PWideChar Identificador da conta
Titular PWideChar Titular da conta
ClOrdID PWideChar Identificador único da ordem (permanente)
Status PWideChar Status da ordem
Date PWideChar Data de execução da ordem
Corresponde ao Callback da solicitação de histórico de ordens. O histórico corresponde apenas as ordens de
day trade.
TAssetListCallback
Manual - ProfitDLL.md 3/17/2023
33 / 41
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual o livro pertence
pwcName PWideChar Descrição do ativo
Corresponde ao callback de solicitação de informação de ativos. É necessário utilizar a função
SetAssetListCallback para que essa função receba dados.
TAssetListInfoCallback
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual a informação pertence
pwcName PWideChar Nome do ativo
pwcDescription PWideChar Descrição do ativo
nMinOrderQtd Integer Mínima quantidade de ordens permitidas
nMaxOrderQtd Integer Máxima quantidade de ordens permitidas
nLote Integer Tamanho de um lote
stSecurityType Integer Tipo do ativo *
ssSecuritySubType Integer Subtipo do ativo **
dMinPriceIncrement Double Incremento mínimo de preço
dContractMultiplier Double Multiplicador do contrato
strValidDate PWideChar Data de validade caso expire
strISIN PWideChar String ISIN do ativo
Corresponde ao Callback de informações de ativos. O campo stSecurityType representa o tipo do ativo
retornado, que pode ser um dos abaixo:
* Tipo do Ativo
0. stFuture
1. stSpot
2. stSpotOption
3. stFutureOption
4. stDerivativeTerm
5. stStock
6. stOption
7. stForward
8. stETF
9. stIndex
10. stOptionExercise
11. stUnknown
12. stEconomicIndicator
Manual - ProfitDLL.md 3/17/2023
34 / 41
13. stMultilegInstrument
14. stCommonStock
15. stPreferredStock
16. stSecurityLoan
17. stOptionOnIndex
18. stRights
19. stCorporateFixedIncome
255. stNelogicaSyntheticAsset
O campo subtipo é uma especificação dentro do tipo e pode ser um dos abaixo:
** Subtipo do ativo
0. ssFXSpot
1. ssGold
2. ssIndex
3. ssInterestRate
4. ssFXRate
5. ssForeignDebt
6. ssAgricultural
7. ssEnergy
8. ssEconomicIndicator
9. ssStrategy
10. ssFutureOption
11. ssVolatility
12. ssSwap
13. ssMiniContract
14. ssFinancialRollOver
15. ssAgriculturalRollOver
16. ssCarbonCredit
17. ssUnknown
18. ssFractionary
19. ssStock
20. ssCurrency
21. ssOTC // OTC MercadoBalcao
22. ssFII // FII Fundo de Investimento Imobiliario
// PUMA 2.0 -Equities
23. ssOrdinaryRights // DO
24. ssPreferredRights // DP
25. ssCommonShares // ON
26. ssPreferredShares // PN
27. ssClassApreferredShares // PNA
28. ssClassBpreferredShares // PNB
29. ssClassCpreferredShares // PNC
30. ssClassDpreferredShares // PND
31. ssOrdinaryReceipts // ON REC
32. ssPreferredReceipts // PN REC
33. ssCommonForward
34. ssFlexibleForward
Manual - ProfitDLL.md 3/17/2023
35 / 41
35. ssDollarForward
36. ssIndexPointsForward
37. ssNonTradeableETFIndex
38. ssPredefinedCoveredSpread
39. ssTraceableETF
40. ssNonTradeableIndex
41. ssUserDefinedSpread
42. ssExchangeDefinedspread // Não usado atualmente
43. ssSecurityLoan
44. ssTradeableIndex
45. ssOthers
46. ssBrazilianDepositaryReceipt // BDR
47. ssFund
48. ssOtherReceipt
49. ssOtherRight
50. ssUNIT
51. ssClassEPreferredShare // PNE
52. ssClassFPreferredShare // PNF
53. ssClassGPreferredShare // PNG
54. ssWarrant
55. ssNonTradableSecurityLending
56. ssForeignIndexETF
57. ssGovernmentETF
58. ssIpoOrFollowOn
59. ssGrossAuction
60. ssNetAuction
61. ssTradableIndexInPartnership
62. ssNontradableIndexInPartnership
63. ssFixedIncomeETF
64. ssNontradableFixedIncomeETF
65. ssOutrightPurchase
66. ssSpecificCollateralRepo
67. ssDebenture
68. ssRealStateReceivableCertificate
69. ssAgribusinessReceivableCertificate
70. ssPromissoryNote
71. ssLetraFinanceira
72. ssAmericanDepositaryReceipt
73. ssUnitInvestmentFund
74. ssReceivableInvestmentFund
75. ssOutrightTPlus1
76. ssRepoTPlus1
77. ssNonTradableGrossSettlement
78. ssNonTradableNetSettlement
79. ssETFPrimaryMarket
80. ssSharesPrimaryMarket
81. ssRightsPrimaryMarket
82. ssUnitPrimaryMarket
83. ssFundPrimaryMarket
Manual - ProfitDLL.md 3/17/2023
36 / 41
84. ssForeignIndexETFPrimaryMarket
85. ssWarrantPrimaryMarket
86. ssReceiptPrimaryMarket
87. ssGermanPublicDebts
88. ssStockRollover
93. ssStrategySpotDollar
94. ssTargetRate
95. ssTradableETFRealState
96. ssNonTradableETFRealEstate
254. ssDefault
TAssetListInfoCallbackV2
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual a informação pertence
pwcName PWideChar Nome do ativo
pwcDescription PWideChar Descrição do ativo
nMinOrderQtd Integer Mínima quantidade de ordens permitidas
nMaxOrderQtd Integer Máxima quantidade de ordens permitidas
nLote Integer Tamanho de um lote
stSecurityType Integer Tipo do ativo *
ssSecuritySubType Integer Subtipo do ativo **
dMinPriceIncrement Double Incremento mínimo de preço
dContractMultiplier Double Multiplicador do contrato
strValidDate PWideChar Data de validade caso expire
strISIN PWideChar String ISIN do ativo
strSetor PWideChar Setor de atuação
strSubSetor PWideChar Subsetor dentro do setor
strSegmento PWideChar Segmento de atuação
Extensão do callback TAssetListInfoCallback, apenas adiciona os campos setor, subsetor e segmento.
TTheoreticalPriceCallback
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo ao qual a informação pertence
dTheoreticalPrice Double Preço teórico
Manual - ProfitDLL.md 3/17/2023
37 / 41
Nome Tipo Descrição
nTheoreticalQtd Int64 Quantidade teórica
Corresponde ao callback para retorno do preço e quantidades teóricas durante o leilão de um ativo.
TAdjustHistoryCallback
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo correspondente ao ajuste
dValue Double Valor do ajuste
strAdjustType PWideChar Tipo de ajuste *
strObserv PWideChar Observação
dtAjuste PWideChar Data do ajuste
dtDeliber PWideChar Data de deliberação
dtPagamento PWideChar Data do pagamento
nAffectPrice Integer Indica se afeta ou não o preço
Corresponde ao Callback de ajustes de um ativo. Para utilizar esse callback é necessário enviá-lo a DLL através
da função SetAdjustHistoryCallback. Preferir utilizar a função SetAdjustHistoryCallbackV2, nela há
uma descrição mais detalhada de como realizar o cálculo do ajuste.
* Tipo de ajuste
'None'
'Unknown'
'JurosRF'
'Dividendo'
'Rendimento'
'Subscricao'
'Desdobramento'
'ResgateTotalRF'
'ResgateTotalRV'
'AmortizacaoRF'
'JurosCapProprio'
'SubsComRenuncia'
'Bonificacao'
'Grupamento'
'JuncaoSerie'
'Cisao'
'Unknown'
TAdjustHistoryCallbackV2
Manual - ProfitDLL.md 3/17/2023
38 / 41
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo correspondente ao ajuste
dValue Double Valor do ajuste
strAdjustType PWideChar Tipo de ajuste *
strObserv PWideChar Observação
dtAjuste PWideChar Data do ajuste
dtDeliber PWideChar Data de deliberação
dtPagamento PWideChar Data do pagamento
nFlags Cardinal Flag de soma (descrita abaixo)
dMult Double Multiplicador
Corresponde ao Callback de ajustes de um ativo. Para utilizar esse callback é necessário enviá-lo a DLL através
da função SetAdjustHistoryCallbackV2.
corresponde ao Callback de ajustes de um ativo. nFlags é um campo de bits b0 a b31, onde o bit 0 (menos
significativo) indica se o ajuste afeta o preço e o bit 1 indica se é um ajuste de Soma. dMult é o valor précomputado que deve ser multiplicado pelo preço para realizar o ajuste, somente é utilizado caso o ajuste não
seja um ajuste de soma e seja um ajuste que afeta preço, informação fornecida no campo nFlags. O valor
-9999 de dMult indica que o mesmo é inválido e não deve ser utilizado. Caso o valor dMult seja inválido,
utiliza-se dValue para realizar o cálculo, sendo uma subtração em caso de ajuste de soma e divisão caso
contrário.
Para realizar o cálculo do ajuste é possível utilizar os parâmetros da seguinte forma:
Quando dMult for um valor válido, o ajuste é feito multiplicando o preço por esse valor.
Quando a flag de soma está setada, o valor de ajuste é subtraído do preço
Quando a flag de soma não está setada, o preço é dividido pelo valor de ajuste.
Pseudo código:
enquanto Data < DataAjuste
se nFlag AND 1 e
(tipo diferente de Grupamento, Junção, Desdobramento e não(Unknown e não(nFlag AND
2))) ou
(tipo é Grupamento, Junção, Desdobramento e não(nFlag AND 2)
então
 se dMult <> -9999
 Resultado := Resultado * dMult
 senão
 se (nFlag AND 2)
 Preço := Preço - ValorAjuste
 senão
 Preço := Preço / ValorAjuste
Manual - ProfitDLL.md 3/17/2023
39 / 41
TChangeCotation
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo em que ocorreu a mudança
pwcDate PWideChar Data da mudança na cotação
nTradeNumber Cardinal Número sequencial do trade em que ocorreu a mudança
dPrice Double Preço novo
Este callback é usado para informar quando ocorrer uma modificação de preço no ativo, informando qual foi
o último preço e hora da negociado. Para utilizar esse callback é necessário enviá-lo a DLL através da função
SetChangeCotationCallback.
TChangeStateTicker
Nome Tipo Descrição
rAssetID TAssetIDRec Ativo em que ocorreu a mudança
pwcDate PWideChar Data da mudança de estado
nState Integre Estado do ativo
Corresponde ao Callback de identificação de alteração de estado do ativo. A data informada é a data em que
houve modificação do estado, apenas alguns estados mostram a data. Os estados possíveis estão listados
abaixo:
0. tcsOpened // Ativo em negociação aberta
2. tcsFrozen
3. tcsInhibited
4. tcsAuctioned // Ativo em leilão
6. tcsClosed // Ativo com negociação fechada
10. tcsPreClosing
13. tcsPreOpening
4. Uso do Produto
Inicializando com Roteamento
Para utilizar a biblioteca é fundamental inicializar os serviços através das funções de inicialização. Mais
especificamente, caso os serviços de roteamento sejam utilizados, deve-se utilizar a função
DLLInitializeLogin, que fará a conexão com os servidores de roteamento e market data.
Essa função é descrita na seção de funções expostas e requer um código de ativação fornecido no momento
da contratação do produto, bem como nome de usuário e senha para efetuar o login no servidor de
autenticação. Os outros parâmetros são callbacks obrigatórios que serão chamados pela DLL durante o uso
que precisam ser especificados no momento da inicialização.
Manual - ProfitDLL.md 3/17/2023
40 / 41
É importante notar que todos os callbacks ocorrem em uma thread chamada ConnectorThread e, portanto,
ocorrem simultaneamente à aplicação cliente. A aplicação cliente deve processar os dados fornecidos através
dos callbacks como dados a serem consumidos de outra thread. Sendo assim, caso necessário, devem tratar a
escrita desses dados com seções críticas ou mutexes.
Os dados recebidos por meio de callbacks são armazenados em uma única fila de dados, portanto, qualquer
processamento demorado dentro das funções de callback pode atrasar a fila de processamento de
mensagens interna da DLL e causar atrasos no recebimento de trades ou outras informações. Para evitar isso,
os dados devem ser processados e enviados para outras threads da aplicação imediatamente, ou realizar o
mínimo de processamento possível. Acessos a banco de dados ou escritas em disco devem ser evitados
durante o processamento de um callback.
Por fim, é importante ressaltar que os callbacks são projetados apenas para receber dados. Portanto, as
funções de requisições à DLL ou qualquer outra função da interface da DLL não devem ser chamadas dentro
de um callback, pois isso pode causar exceções inesperadas e comportamento indefinido.
Mais detalhes de implementação podem ser esclarecidos nos exemplos disponibilizados.
Inicializando com Market Data
O processo de inicialização do Market Data é análogo à inicialização com Roteamento, com a diferença do
nome da função de inicialização DLLInitializeMarketLogin e redução de callbacks enviados por
parâmetro, pois os mesmos são relacionados a ordens ou contas de roteamento.
Tipos de dados
Todos os tipos citados nesse documento são tipos especificados na linguagem Delphi, abaixo estão alguns
links para conversão ou mapeamento desses tipos para as linguagens dos exemplos.
Mapeamento de tipos de Delphi para C
https://docwiki.embarcadero.com/RADStudio/Tokyo/en/Delphi_to_C%2B%2B_types_mapping
Conversão de tipos C para Python
https://docs.python.org/2/library/ctypes.html
Conversão de tipos de Delphi para C#
http://www.netcoole.com/delphi2cs/datatype.htm
Linkagem em 32 bits
Para utilizar a biblioteca em 32 bits é necessário que a aplicação também seja compilada em 32 bits. Por ser
32 bits, há uma limitação de memória em 4GB, que será compartilhada entre a biblioteca e a aplicação cliente.
Portanto, não é recomendado fazer requisições de muitos dados em apenas uma requisição, pois isso pode
exceder o limite de memória do processo.
C#
Utilizando Visual Studio, é necessário alterar a plataforma alvo em Configuration Manager de
Any CPU para x86.
Manual - ProfitDLL.md 3/17/2023
41 / 41
Python
É necessário que o interpretador python.exe também seja 32 bits. Além disso existe um bug em
python 32 bits em que um callback contendo um tipo maior que 32 bits falha e causa uma
exception. Link para acompanhamento: https://bugs.python.org/issue41021. Por isso solicitamos
que o cliente caso queira utilizar python 32 bits utilize a versão 3.6.2 que foi testada pela equipe
da Nelogica e não possui esse problema.
Para as demais linguagens é necessário apenas trocar o modo de compilação para 32 bits.
Linkagem em 64 bits
Para utilizar a biblioteca em 64 bits a aplicação também deve ser compilada em 64 bits. A convenção de
chamadas continua sendo stdcall, assim como na versão 32 bits. Não existem problemas conhecidos para as
linguagens de exemplo na versão 64 bits, portanto não há uma versão recomendada, é possível o uso das
últimas versões de cada uma das linguagens.
A versão 64 bits não possui limitação de memória e portanto pode utilizar o máximo de memória disponível
no sistema, podendo requisitar mais dados em uma requisição, limitado pela quantidade de RAM disponível.
