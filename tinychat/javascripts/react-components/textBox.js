/** @jsx React.DOM */

define(["react"],function(React) {
  return React.createClass({
    getInitialState:function(){
      return {
        post:""
      };
    },
    newPostMessage:function(){
      if (this.state.post !== ""){
        this.props.newPostMessage(this.state.post);
        this.setState({
          post:""
        });
      }
    },
    handleChange:function(value){
      this.setState({
        post:value
      });
    },
    render:function(){
      return (
        <div className="textboxWrapper">
            <input type="text" className="textInput" value={this.state.post} onChange={(e) =>this.handleChange(e.target.value)} />
            <input type="submit" value="Add Message" onClick={() => this.newPostMessage()} />
        </div>
      )
    }
  });
});
