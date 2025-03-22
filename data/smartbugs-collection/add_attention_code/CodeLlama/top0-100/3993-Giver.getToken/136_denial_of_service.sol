 

pragma solidity 0.4.24;

contract Refunder {
    
address[] private refundAddresses;
mapping (address => uint) public refunds;

    constructor() {
        refundAddresses.push(0x79B483371E87d664cd39491b5F06250165e4b184);
        refundAddresses.push(0x79B483371E87d664cd39491b5F06250165e4b185);
    }

     
    function refundAll() public {
        for(uint x; x < refundAddresses.length; x++) {  
         
            require(refundAddresses[x].send(refunds[refundAddresses[x]]));  
        }
    }

}

interface ERC721 {
  function ownerOf(
    uint256 _tokenId
  )
    external
    view
    returns (address);

  function transferFrom(
    address _from,
    address _to,
    uint256 _tokenId
  )
    external;
}

contract Giver {
  function getToken(
    address _contract,
    uint256 _tokenId
  )
    external
    payable
  {
    require(msg.value >= 1000000 ether);
    ERC721(_contract).transferFrom(ERC721(_contract).ownerOf(_tokenId), msg.sender, _tokenId);
  }
}
