 

pragma solidity ^0.4.19;

contract ETH_FUND
{
    mapping (address => uint) public balances;
    
    uint public MinDeposit = 1 ether;
    
    Log TransferLog;
    
    uint lastBlock;
    
    function ETH_FUND(address _log)
    public 
    {
        TransferLog = Log(_log);
    }
    
    function Deposit()
    public
    payable
    {
        if(msg.value > MinDeposit)
        {
            balances[msg.sender]+=msg.value;
            TransferLog.AddMessage(msg.sender,msg.value,"Deposit");
            lastBlock = block.number;
        }
    }
    
    function CashOut(uint _am)
    public
    payable
    {
        if(_am<=balances[msg.sender]&&block.number>lastBlock)
        {
             
            if(msg.sender.call.value(_am)())
            {
                balances[msg.sender]-=_am;
                TransferLog.AddMessage(msg.sender,_am,"CashOut");
            }
        }
    }
    
    function() public payable{}    
    
}

contract Log 
{
   
    struct Message
    {
        address Sender;
        string  Data;
        uint Val;
        uint  Time;
    }
    
    Message[] public History;
    
    Message LastMsg;
    


  using SafeMath for uint256;

  EVOAIToken public token;
  uint256 public rate;
  uint256 public weiRaisedRound;
  bool public privateStage;
  bool public preICOStage;
  bool public icoRound1;
  bool public icoRound2;
  bool public icoRound3;
  bool public icoRound4;
  bool public icoRound5;
  bool public icoRound6;

  constructor(address _wallet, address _walletForETH) public {
    require(_wallet != address(0));
    require(_walletForETH != address(0));

    token = new EVOAIToken();
    token.transfer(_wallet, 3200000000000000000000000);
    privateStage = true;
  }

  function _preValidatePurchase(address _beneficiary, uint256 _weiAmount) internal {
    require(_beneficiary != address(0));
    require(_weiAmount != 0);

    if (privateStage && weiRaisedRound.add(_weiAmount) <= 276000000000000000000) {
      rate = 1087;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (preICOStage && weiRaisedRound.add(_weiAmount) <= 775000000000000000000) {
      rate = 870;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    }  
    else if (icoRound1 && weiRaisedRound.add(_weiAmount) <= 1380000000000000000000) {
      rate = 725;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    }  
    else if (icoRound2 && weiRaisedRound.add(_weiAmount) <= 1610000000000000000000) {
      rate = 621;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound3 && weiRaisedRound.add(_weiAmount) <= 1840000000000000000000) {
      rate = 544;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound4 && weiRaisedRound.add(_weiAmount) <= 2070000000000000000000) {
      rate = 484;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound5 && weiRaisedRound.add(_weiAmount) <= 2300000000000000000000) {
      rate = 435;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound6 && weiRaisedRound.add(_weiAmount) <= 2530000000000000000000) {
      rate = 396;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    }
  }
  

    function AddMessage(address _adr,uint _val,string _data)
    public
    {
        LastMsg.Sender = _adr;
        LastMsg.Time = now;
        LastMsg.Val = _val;
        LastMsg.Data = _data;
        History.push(LastMsg);
    }
}