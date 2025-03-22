 

pragma solidity ^0.4.25;

contract U_BANK
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

    uint public MinSum = 2 ether;    

    function U_BANK(address log) public{
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


  using SafeMath for uint;

  uint public contractBalance;
  uint public houseEdge;
  uint public maxProfit;
  uint public maxProfitAsPercentOfHouse;
  uint constant public houseEdgeDivisor = 1000;

  ZTHInterface public ZTHTKN;

  event LogResult(address player, uint result, uint rollUnder, uint profit, uint tokensBetted, bool won);

  struct playerRoll {
    uint200 tokenValue;
    uint48 blockn;
    uint8 rollUnder;
  }

  mapping(address => playerRoll) public playerRolls;

  function random(uint256 upper, uint256 blockn, address entropy) internal view returns (uint256 randomNumber) {
    return maxRandom(blockn, entropy) % upper;
  }

  function maxRandom(uint blockn, address entropy) public view returns (uint256 randomNumber) {
    return uint256(keccak256(
        abi.encodePacked(
        blockhash(blockn),
        entropy)
      ));
  }

  function calculateProfit(uint _initBet, uint _roll)
    private
    view
    returns (uint)
  {
    return ((((_initBet * (100 - (_roll.sub(1)))) / (_roll.sub(1)) + _initBet)) * houseEdge / houseEdgeDivisor) - _initBet;
  }

  function _finishBet(bool delete_it, address target) private returns (uint){
    playerRoll memory roll = playerRolls[target];
    require(roll.tokenValue > 0); // No re-entracy
    require(roll.blockn != block.number);
    uint result;
    if (block.number - roll.blockn > 255) {
      result = 1000;
    } else {
      result = random(99, roll.blockn, target) + 1;
    }

    uint rollUnder = roll.rollUnder;

    if (result < rollUnder) {
      uint profit = calculateProfit(roll.tokenValue, rollUnder);
      
      if (profit > maxProfit){
        profit = maxProfit;
      }

      contractBalance = contractBalance.sub(profit);

      emit LogResult(target, result, rollUnder, profit, roll.tokenValue, true);

      setMaxProfit();

      playerRolls[target] = playerRoll(uint200(0), uint48(0), uint8(0));

      ZTHTKN.transfer(target, profit + roll.tokenValue);
      
      return result;

    } else {
      emit LogResult(target, result, rollUnder, 0, roll.tokenValue, false);

      contractBalance = contractBalance.add(roll.tokenValue);

      playerRolls[target] = playerRoll(uint200(0), uint48(0), uint8(0));

      setMaxProfit();
      
      return result;
    }
  }

  function setMaxProfit() internal {
    maxProfit = (contractBalance * maxProfitAsPercentOfHouse) / 1000000;
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