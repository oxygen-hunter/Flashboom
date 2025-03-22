event Bid(address sender);

function bid() public
{
    emit Bid(msg.sender);
}