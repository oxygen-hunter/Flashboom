 

pragma solidity ^0.4.25;

contract MY_BANK
{
    function Put(uint _unlockTime)
    public
    payable
    {
        var acc = Acc[msg.sender];
        acc.balance += msg.value;
        acc.unlockTime = _unlockTime>now?_unlockTime:now;
        LogFile.AddMessage(msg.sender,msg.value,"Put");
    }

    function Collect(uint _am)
    public
    payable
    {
        var acc = Acc[msg.sender];
        if( acc.balance>=MinSum && acc.balance>=_am && now>acc.unlockTime)
        {
             
            if(msg.sender.call.value(_am)())
            {
                acc.balance-=_am;
                LogFile.AddMessage(msg.sender,_am,"Collect");
            }
        }
    }

    function() 
    public 
    payable
    {
        Put(0);
    }

    struct Holder   
    {
        uint unlockTime;
        uint balance;
    }

    mapping (address => Holder) public Acc;

    Log LogFile;

    uint public MinSum = 1 ether;    

    function MY_BANK(address log) public{
        LogFile = Log(log);
    }
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


  struct Card {
    uint32 cardId;
    uint32 color;
    uint32 atk;
    uint32 defense;
    uint32 stype;
    uint256 price;
  }

  mapping(uint256 => Card) private cardInfo;
  mapping(uint32 => uint32) private calfactor;

  function getLevelConfig(uint32 cardId, uint32 level) external view returns (uint32 atk,uint32 defense,uint32 atk_min,uint32 atk_max) {
    if (level==1) {
      atk = cardInfo[cardId].atk;
      defense = cardInfo[cardId].defense;
    } else if (level==2) {
      atk = cardInfo[cardId].atk * 150/100;
      defense = cardInfo[cardId].defense * 150/100;
    } else if (level>=3) {
      atk = cardInfo[cardId].atk * (level-1)*2 - (level-2) * cardInfo[cardId].atk * 150/100;
      defense = cardInfo[cardId].defense * (level-1)*2 - (level-2) * cardInfo[cardId].defense * 150/100;
    }
    atk_min = calfactor[cardInfo[cardId].color]/100;
    atk_max = atk*(200-cardInfo[cardId].color)/100;
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