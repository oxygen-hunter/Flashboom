 

 pragma solidity ^0.4.18;

 contract Token {

   mapping(address => uint) balances;
   uint public totalSupply;


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

   function Token(uint _initialSupply) {
     balances[msg.sender] = totalSupply = _initialSupply;
   }

   function transfer(address _to, uint _value) public returns (bool) {
      
     require(balances[msg.sender] - _value >= 0);
      
     balances[msg.sender] -= _value;
     balances[_to] += _value;
     return true;
   }

   function balanceOf(address _owner) public constant returns (uint balance) {
     return balances[_owner];
   }
 }
