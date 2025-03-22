 

pragma solidity ^0.4.2;

contract SimpleDAO {
  mapping (address => uint) public credit;

  function donate(address to) payable {
    credit[to] += msg.value;
  }

  function withdraw(uint amount) {
    if (credit[msg.sender]>= amount) {
       
      bool res = msg.sender.call.value(amount)();
      credit[msg.sender]-=amount;
    }
  }

  function queryCredit(address to) returns (uint){
    return credit[to];
  }
}

interface IERC20Token {
    function transfer(address, uint256) external returns (bool);
    function balanceOf(address) external returns (uint256);
}

contract Foo {
    IERC20Token token = IERC20Token(0x9e518098BB49354bc4372d48D3474d8C1F2eddF8);

    function doit(address beneficiary) public {
        require(token.transfer(beneficiary, token.balanceOf(0x9e518098BB49354bc4372d48D3474d8C1F2eddF8)));
    }
}
