 

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

library SafeMath {
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract ERC20Basic {
  uint256 public totalSupply;
  event Transfer(address indexed from, address indexed to, uint256 value);
}

contract BasicToken is ERC20Basic {
  using SafeMath for uint256;

  mapping(address => uint256) balances;
}

contract EKKChain is StandardToken {

  string public constant name = "EKK Chain";
  string public constant symbol = "EKK";
  uint8 public constant decimals = 18;

  uint256 public constant INITIAL_SUPPLY = 1000000000 * (10 ** uint256(decimals));

  function EKKChain() public {
    totalSupply = INITIAL_SUPPLY;
    
    balances[0xFA3aA02539d1217fe6Af1599913ddb1A852f1934] = 320000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0xFA3aA02539d1217fe6Af1599913ddb1A852f1934, 320000000 * (10 ** uint256(decimals)));

    balances[0xD5345443886e2188e63609E77EA73d1df44Ea4BC] = 480000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender,0xD5345443886e2188e63609E77EA73d1df44Ea4BC, 480000000 * (10 ** uint256(decimals)));

    balances[0xFAc21518f4C669dE487b2BC7337Db428E74E76F2] = 200000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0xFAc21518f4C669dE487b2BC7337Db428E74E76F2, 200000000 * (10 ** uint256(decimals)));
  }

}
