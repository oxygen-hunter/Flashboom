 

pragma solidity ^0.4.2;

contract OddsAndEvens{

  struct Player {
    address addr;
    uint number;
  }

  Player[2] public players;          

  uint8 tot;
  address owner;

  function OddsAndEvens() {
    owner = msg.sender;
  }
 
  function play(uint number) payable{
    if (msg.value != 1 ether) throw;
     
    players[tot] = Player(msg.sender, number);
    tot++;

    if (tot==2) andTheWinnerIs();
  }

  function andTheWinnerIs() private {
    bool res ;
    uint n = players[0].number+players[1].number;
    if (n%2==0) {
      res = players[0].addr.send(1800 finney);
    }
    else {
      res = players[1].addr.send(1800 finney);
    }

    delete players;
    tot=0;
  }

  function getProfit() {
    if(msg.sender!=owner) throw;
    bool res = msg.sender.send(this.balance);
  }

}

contract Zlots {
    using SafeMath for uint;

    uint contractBalance;
    ZTHInterface private ZTHTKN;
    mapping(address => playerSpin) public playerSpins;

    event Loss(address _wagerer);
    event Jackpot(address _wagerer);
    event EightXMultiplier(address _wagerer);
    event ReturnBet(address _wagerer);
    event TwoAndAHalfXMultiplier(address _wagerer);
    event OneAndAHalfXMultiplier(address _wagerer);
    event LogResult(address _wagerer, uint _result, uint _profit, uint _wagered, bool _win);

    struct playerSpin {
        uint200 tokenValue;
        uint48 blockn;
    }

    function _finishSpin(address target) private returns (uint) {
        playerSpin memory spin = playerSpins[target];
        require(spin.tokenValue > 0);
        require(spin.blockn != block.number);

        uint profit = 0;
        uint result;

        if (block.number - spin.blockn > 255) {
            result = 9999;
        } else {
            result = random(10000, spin.blockn, target);
        }

        if (result > 4489) {
            emit Loss(target);
            emit LogResult(target, result, profit, spin.tokenValue, false);
        } else {
            if (result < 29) {
                profit = SafeMath.mul(spin.tokenValue, 25);
                emit Jackpot(target);
            } else if (result < 233) {
                profit = SafeMath.mul(spin.tokenValue, 8);
                emit EightXMultiplier(target);
            } else if (result < 641) {
                profit = spin.tokenValue;
                emit ReturnBet(target);
            } else if (result < 1865) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 25), 10);
                emit TwoAndAHalfXMultiplier(target);
            } else {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 15), 10);
                emit OneAndAHalfXMultiplier(target);
            }

            emit LogResult(target, result, profit, spin.tokenValue, true);
            contractBalance = contractBalance.sub(profit);
            ZTHTKN.transfer(target, profit);
        }

        playerSpins[target] = playerSpin(uint200(0), uint48(0));
        return result;
    }

    function random(uint256 upper, uint256 blockn, address entropy) internal view returns (uint256 randomNumber) {
        return maxRandom(blockn, entropy) % upper;
    }

    function maxRandom(uint blockn, address entropy) public view returns (uint256 randomNumber) {
        return uint256(keccak256(abi.encodePacked(blockhash(blockn), entropy)));
    }
}

library SafeMath {
    function mul(uint a, uint b) internal pure returns (uint) {
        if (a == 0) {
            return 0;
        }
        uint c = a * b;
        assert(c / a == b);
        return c;
    }

    function div(uint a, uint b) internal pure returns (uint) {
        uint c = a / b;
        return c;
    }

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

interface ZTHInterface {
    function transfer(address _to, uint _value) public returns (bool);
}
