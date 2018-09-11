let component = ReasonReact.statelessComponent("Todo");

let make = (~id, _children) => {
  ...component, /* spread the template's other defaults into here  */
  render: _self => <div> (ReasonReact.string(id)) </div>,
};