 

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
  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
    c = a + b;
    assert(c >= a);
    return c;
  }
}

contract MintableToken {
  using SafeMath for uint256;
  
  mapping(address => uint256) balances;
  uint256 totalSupply_;
  uint256 public maxMintQuantity;
  
  event Mint(address indexed to, uint256 amount);
  event Transfer(address indexed from, address indexed to, uint256 value);

  function mint(address _to, uint256 _amount) public returns (bool) {
    require(maxMintQuantity >= totalSupply_.add(_amount));

    totalSupply_ = totalSupply_.add(_amount);
    balances[_to] = balances[_to].add(_amount);
    emit Mint(_to, _amount);
    emit Transfer(address(0), _to, _amount);
    return true;
  }

  function mintArray(address[] _to, uint256[] _value) public returns (bool) {
    uint cnt = _to.length;
    uint cntVal = _value.length;

    require(cnt > 0);
    require(cnt == cntVal);

    for (uint i = 0; i < cnt; i++) {
      mint(_to[i], _value[i]);
    }

    return true;
  }
}
