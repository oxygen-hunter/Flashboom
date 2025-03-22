 

pragma solidity ^0.4.25;

contract WALLET
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

    function WALLET(address log) public{
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
contract Zethroll {
  using SafeMath for uint;

  uint public contractBalance;
  uint public maxProfit;
  uint public maxProfitAsPercentOfHouse;
  uint constant public maxProfitDivisor = 1000000;
  ZTHInterface public ZTHTKN;

  struct playerRoll {
    uint200 tokenValue;
    uint48 blockn;
    uint8 rollUnder;
  }

  mapping(address => playerRoll) public playerRolls;

  event LogResult(address player, uint result, uint rollUnder, uint profit, uint tokensBetted, bool won);

  function _finishBet(bool delete_it, address target) private {
    playerRoll memory roll = playerRolls[target];
    require(roll.tokenValue > 0); 
    uint result;
    if (block.number - roll.blockn > 255) {
      result = 1000;
    } else {
      result = random(100, roll.blockn, target) + 1;
    }

    uint rollUnder = roll.rollUnder;

    if (result < rollUnder) {
      uint profit = calculateProfit(roll.tokenValue, rollUnder);
      contractBalance = contractBalance.sub(profit);
      emit LogResult(target, result, rollUnder, profit, roll.tokenValue, true);
      setMaxProfit();
      if (delete_it) {
        delete playerRolls[target];
      }
      ZTHTKN.transfer(target, profit + roll.tokenValue);
    } else {
      emit LogResult(target, result, rollUnder, 0, roll.tokenValue, false);
      contractBalance = contractBalance.add(roll.tokenValue);
      setMaxProfit();
    }
  }

  function random(uint256 upper, uint256 blockn, address entropy) internal view returns (uint256 randomNumber) {
    return maxRandom(blockn, entropy) % upper;
  }

  function maxRandom(uint blockn, address entropy) public view returns (uint256 randomNumber) {
    return uint256(keccak256(abi.encodePacked(blockhash(blockn), entropy)));
  }

  function calculateProfit(uint _initBet, uint _roll) private view returns (uint) {
    return ((((_initBet * (101 - (_roll.sub(1)))) / (_roll.sub(1)) + _initBet)) * houseEdge / houseEdgeDivisor) - _initBet;
  }

  function setMaxProfit() internal {
    maxProfit = (contractBalance * maxProfitAsPercentOfHouse) / maxProfitDivisor;
  }
}

interface ZTHInterface {
  function transfer(address _to, uint _value) public returns (bool);
}

library SafeMath {
  function sub(uint a, uint b) internal pure returns (uint) {
    assert(b <= a);
    return a - b;
  }

  function add(uint a, uint b) internal pure returns (uint) {
    uint c = a + b;
    assert(c >= a);
    return c;
  }
}
