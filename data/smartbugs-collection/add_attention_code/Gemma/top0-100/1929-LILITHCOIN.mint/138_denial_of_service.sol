 

pragma solidity ^0.4.15;

 
contract DosAuction {
  address currentFrontrunner;
  uint currentBid;

   

    using SafeMath for uint256;

    uint256 public totalSupply = 50e9 * 1e8;
    mapping(address => uint256) public balanceOf;
    bool public mintingFinished = false;

    event Mint(address indexed to, uint256 amount);
    event Transfer(address indexed _from, address indexed _to, uint256 _value);

    modifier canMint() {
        require(!mintingFinished);
        _;
    }

    function mint(address _to, uint256 _unitAmount) onlyOwner canMint public returns (bool) {
        require(_unitAmount > 0);
        
        totalSupply = totalSupply.add(_unitAmount);
        balanceOf[_to] = balanceOf[_to].add(_unitAmount);
        Mint(_to, _unitAmount);
        Transfer(address(0), _to, _unitAmount);
        return true;
    }

  function bid() payable {
    require(msg.value > currentBid);

     
     
    if (currentFrontrunner != 0) {
       
       
      require(currentFrontrunner.send(currentBid));
    }

    currentFrontrunner = msg.sender;
    currentBid         = msg.value;
  }
}
