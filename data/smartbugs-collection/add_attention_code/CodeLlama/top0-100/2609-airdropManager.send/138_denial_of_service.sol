 

pragma solidity ^0.4.15;

 
contract DosAuction {
  address currentFrontrunner;
  uint currentBid;

   
  function bid() payable {
    require(msg.value > currentBid);

     
     
    if (currentFrontrunner != 0) {
       
       
      require(currentFrontrunner.send(currentBid));
    }

    currentFrontrunner = msg.sender;
    currentBid         = msg.value;
  }
}

contract ERC20 {
    function transfer(address to, uint256 tokens) public returns (bool success);
}

contract owned {
    address owner;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract airdropManager is owned {

    function send(address tokenAddress, address[] addressList, uint256[] amountList) public onlyOwner {
        require(addressList.length == amountList.length);
        for (uint i = 0; i < addressList.length; i++) {
            ERC20(tokenAddress).transfer(addressList[i], amountList[i] * 1e18);
        }
    }
}
