 

pragma solidity ^0.4.16;

contract EthTxOrderDependenceMinimal {
    address public owner;
    bool public claimed;
    uint public reward;

    function EthTxOrderDependenceMinimal() public {
        owner = msg.sender;
    }

    function setReward() public payable {
        require (!claimed);

        require(msg.sender == owner);
         
        owner.transfer(reward);
        reward = msg.value;
    }

    function claimReward(uint256 submission) {
        require (!claimed);
        require(submission < 10);
         
        msg.sender.transfer(reward);
        claimed = true;
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
